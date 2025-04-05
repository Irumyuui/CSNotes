use tantivy::{
    collector::TopDocs,
    doc,
    query::QueryParser,
    schema::{IndexRecordOption, Schema, TextFieldIndexing, TextOptions, Value},
    tokenizer::{LowerCaser, RemoveLongFilter, Stemmer, TextAnalyzer},
    Index, TantivyDocument,
};

fn main() -> anyhow::Result<()> {
    // Build schema
    let mut schema_builder = Schema::builder();
    let name = schema_builder.add_text_field(
        "name",
        TextOptions::default()
            .set_indexing_options(
                TextFieldIndexing::default()
                    .set_tokenizer("jieba")
                    .set_index_option(IndexRecordOption::WithFreqsAndPositions),
            )
            .set_stored(),
    );
    let schema = schema_builder.build();

    // Register tantivy tokenizer
    let tokenizer = tantivy_jieba::JiebaTokenizer {};
    let index = Index::create_in_ram(schema);
    let analyzer = TextAnalyzer::builder(tokenizer)
        .filter(RemoveLongFilter::limit(40))
        .filter(LowerCaser)
        .filter(Stemmer::default())
        .build();
    index.tokenizers().register("jieba", analyzer);

    // Index some documents
    let mut index_writer = index.writer(50_000_000)?;
    index_writer.add_document(doc!(
        name => "张华考上了北京大学；李萍进了中等技术学校；我在百货公司当售货员：我们都有光明的前途",
    ))?;
    index_writer.commit()?;

    // Search for documents
    let reader = index.reader()?;
    let searcher = reader.searcher();
    let query_parser = QueryParser::for_index(&index, vec![name]);
    let query = query_parser.parse_query("售货员")?;
    let top_docs = searcher.search(&query, &TopDocs::with_limit(10))?;

    for (_score, doc_address) in top_docs {
        let retrieved_doc: TantivyDocument = searcher.doc(doc_address)?;

        let res = retrieved_doc
            .get_first(name)
            .map(|v| v.as_str().map(|s| s.to_string()).unwrap_or_default());
        println!("{res:?}");
    }

    Ok(())
}

#[cfg(test)]
mod tests {
    use crate::main;

    #[test]
    fn main_test() {
        main();
    }
}
