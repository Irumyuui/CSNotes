#![allow(unused_variables)]
#![allow(unused_mut)]
#![allow(unused_imports)]

use std::io::Write;
use std::collections::HashMap;

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>
}
impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut line = String::new();
            std::io::stdin().read_line(&mut line).expect("Failed read");
            self.buffer = line.split_whitespace().rev().map(String::from).collect();
        }
    }
}

fn main() {
    let mut cin = Scanner::default();
    let mut cout = std::io::BufWriter::new(std::io::stdout());

}