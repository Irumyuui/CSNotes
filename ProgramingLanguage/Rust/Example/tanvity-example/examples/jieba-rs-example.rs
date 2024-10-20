fn main() {
    let jieba = jieba_rs::Jieba::new();
    let words = jieba.cut("我们中出了一个叛徒", false);
    // assert_eq!(words, vec!["我们", "中", "出", "了", "一个", "叛徒"]);clea
    println!("{:?}", words);
}

#[cfg(test)]
mod tests {
    use crate::main;

    #[test]
    fn main_test() {
        main();
    }
}
