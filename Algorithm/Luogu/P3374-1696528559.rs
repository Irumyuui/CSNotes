#![allow(dead_code)]
#![allow(unused_variables)]
#![allow(unused_imports)]

use std::io::{self, prelude::*};
use std::str;

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

struct FenwickTree<T> {
    bit : Vec<T>,
    opt : fn(T,T)->T,
}
impl<T : Copy + From<i32>> FenwickTree<T> {
    fn new(n : usize, value : T, opt : fn(T,T)->T) -> Self {
        Self {
            bit : vec![value; n + 1],
            opt
        }
    }
    fn apply(&mut self, mut x : isize, d : T) {
        x += 1;
        while x < self.bit.len().try_into().unwrap() {
            self.bit[x as usize] = (self.opt)(self.bit[x as usize], d);
            x += x & -x;
        }
    }
    fn ask(&self, mut x : isize) -> T {
        let mut ret : T = T::from(0);
        while x > 0 {
            ret = (self.opt)(self.bit[x as usize], ret);
            x -= x & -x;
        }
        return ret;
    }
}

fn main() {
    let (stdin, stdout) = (io::stdin(), io::stdout());
    let mut scan = Scanner::new(stdin.lock());
    let mut out = io::BufWriter::new(stdout.lock());
    
    let n = scan.next::<usize>();
    let q = scan.next::<usize>();

    let mut bit = FenwickTree::<i64>::new(n, 0 as i64, |x, y| x + y);
    for i in 0..n.try_into().unwrap() {
        let x = scan.next::<i64>();
        bit.apply(i, x);
    }

    for _ in 0..q {
        let opt = scan.next::<i32>();
        
        if opt == 1 {
            let x = scan.next::<isize>() - 1;
            let d = scan.next::<i64>();
            bit.apply(x, d);
        } else {
            let l = scan.next::<isize>();
            let r = scan.next::<isize>();
            out.write_fmt(format_args!("{}\n", bit.ask(r) - bit.ask(l - 1))).unwrap();
        }
    }
}