#![allow(dead_code)]
#![allow(unused_variables)]
#![allow(unused_imports)]

use std::fmt::write;
use std::io::{self, prelude::*, BufWriter};
use std::process::id;
use std::{str, vec};
use std::cmp::Ordering;

struct Scanner<R> {
    reader: R,
    buf_str: Vec<u8>,
    buf_iter: str::SplitAsciiWhitespace<'static>,
}
impl<R : io::BufRead> Scanner<R> {
    fn new(reader: R) -> Self {
        Self { reader, buf_str: Vec::new(), buf_iter: "".split_ascii_whitespace() }
    }
    fn next<T: str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return token.parse().ok().expect("Failed parse");
            }
            self.buf_str.clear();
            self.reader.read_until(b'\n', &mut self.buf_str).expect("Failed read");
            self.buf_iter = unsafe {
                let slice = str::from_utf8_unchecked(&self.buf_str);
                std::mem::transmute(slice.split_ascii_whitespace())
            }
        }
    }
}

fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut scan = Scanner::new(stdin.lock());
    let mut out = std::io::BufWriter::new(stdout.lock());

    let n : usize = scan.next();
    let mut seg = Vec::<(u32, u32)>::with_capacity(n);
    for i in 0..n {
        let l : u32 = scan.next();
        let r : u32 = scan.next();
        seg.push((l, r));
    }
    seg.sort_by(|&a, &b| a.1.cmp(&b.1));
    let mut ret = Vec::<(u32, u32)>::with_capacity(n);
    ret.push(*seg.first().unwrap());
    for (l, r) in &seg {
        if ret.last().unwrap().1 <= *l {
            ret.push((*l, *r));
        }
    }
    write!(out, "{}\n", ret.len()).unwrap();
}
