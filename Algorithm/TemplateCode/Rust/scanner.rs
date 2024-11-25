pub struct Scanner<R> {
    reader: R,
    buffer: Vec<String>,
}

impl<R> Scanner<R>
where
    R: std::io::BufRead,
{
    pub fn new(reader: R) -> Self {
        Self {
            reader,
            buffer: Default::default(),
        }
    }

    pub fn next<T>(&mut self) -> T
    where
        T: std::str::FromStr,
    {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }

            let mut input = String::new();
            self.reader.read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

// fn main() {
//     let mut scanner = Scanner::new(std::io::stdin().lock());
//     let out = std::io::BufWriter::new(std::io::stdout().lock());
// }