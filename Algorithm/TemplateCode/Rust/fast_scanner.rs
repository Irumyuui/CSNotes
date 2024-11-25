use std::io::Write;

pub struct Scanner<R> {
    reader: R,
    buf_str: Vec<u8>,
    buf_iter: std::str::SplitAsciiWhitespace<'static>,
}

impl<R: std::io::BufRead> Scanner<R> {
    pub fn new(reader: R) -> Self {
        Self {
            reader,
            buf_str: Default::default(),
            buf_iter: "".split_ascii_whitespace(),
        }
    }

    pub fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return token.parse().ok().expect("Parse error");
            }

            self.buf_str.clear();
            self.reader
                .read_until(b'\n', &mut self.buf_str)
                .expect("Read error");
            self.buf_iter = unsafe {
                std::mem::transmute(
                    std::str::from_utf8_unchecked(&self.buf_str).split_ascii_whitespace(),
                )
            };
        }
    }
}

#[cfg(unix)]
pub fn standard_io() -> (impl std::io::BufRead, impl std::io::Write) {
    use std::{
        fs::File,
        io::{stdin, stdout, BufReader, BufWriter},
        os::unix::prelude::{AsRawFd, FromRawFd},
    };

    unsafe {
        let stdin = File::from_raw_fd(stdin().as_raw_fd());
        let stdout = File::from_raw_fd(stdout().as_raw_fd());
        (BufReader::new(stdin), BufWriter::new(stdout))
    }
}

#[cfg(windows)]
pub fn standard_io() -> (impl std::io::BufRead, impl std::io::Write) {
    use std::{
        fs::File,
        io::{stdin, stdout, BufReader, BufWriter},
        os::windows::io::{AsRawHandle, FromRawHandle},
    };

    unsafe {
        let stdin = File::from_raw_handle(stdin().as_raw_handle());
        let stdout = File::from_raw_handle(stdout().as_raw_handle());
        (BufReader::new(stdin), BufWriter::new(stdout))
    }
}

fn main() {
    let (cin, mut cout) = standard_io();
    let mut scan = Scanner::new(cin);

    let n: usize = scan.next();
    let mut a: Vec<i32> = Vec::with_capacity(n);
    for _ in 0..n {
        a.push(scan.next());
    }

    let mut ans = 0;
    for x in a {
        if x <= 99 {
            ans += 1;
        }
    }

    writeln!(&mut cout, "{}", ans).unwrap();
}
