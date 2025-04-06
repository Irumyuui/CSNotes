这个是我用来做题用的板子。

```rust
use std::{
    io::{BufRead, BufReader, stdin},
    str::FromStr,
};

pub struct Scanner<R: BufRead> {
    reader: R,
    buf: Vec<String>,
}

impl<R: BufRead> Scanner<R> {
    pub fn new(reader: R) -> Self {
        Self {
            reader,
            buf: Vec::new(),
        }
    }

    pub fn read<T: FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf.pop() {
                return token.parse().ok().unwrap();
            }
            let mut line = String::new();
            self.reader.read_line(&mut line).unwrap();
            self.buf.extend(line.split_whitespace().map(String::from));
        }
    }
}

fn main() {
    #[allow(unused)]
    let scan = Scanner::new(BufReader::new(stdin()));
}
```