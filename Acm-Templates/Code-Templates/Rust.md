这个是我用来做题用的板子。

```rust
use crate::prelude::*;

fn main() {
    #[allow(unused)]
    let mut scan = Scanner::new(buf_stdin());

    let case: usize = scan.read();
    #[allow(unused)]
    'main: for _ in 0..case {
        todo!()
    }
}

pub mod prelude {
    #![allow(clippy::missing_transmute_annotations)]

    use std::{
        cell::RefCell,
        io::{BufRead, BufReader, BufWriter, StdinLock, StdoutLock, stdin, stdout},
        str::{self, FromStr, SplitAsciiWhitespace},
    };

    pub trait BoolExt {
        fn map_result(self) -> &'static str;

        fn select<T>(self, true_val: T, false_val: T) -> T;
    }

    pub trait ReadNext {
        #[allow(unused)]
        fn read<T: FromStr>(&mut self) -> T;
    }

    impl BoolExt for bool {
        fn map_result(self) -> &'static str {
            match self {
                true => "YES",
                false => "NO",
            }
        }

        #[inline(always)]
        fn select<T>(self, true_val: T, false_val: T) -> T {
            if self { true_val } else { false_val }
        }
    }

    pub struct Scanner<R> {
        reader: R,
        buf: Vec<u8>,
        token_iter: SplitAsciiWhitespace<'static>,
    }

    impl<R: BufRead> Scanner<R> {
        pub fn new(reader: R) -> Self {
            Self {
                reader,
                buf: Vec::new(),
                token_iter: "".split_ascii_whitespace(),
            }
        }
    }

    impl<R: BufRead> ReadNext for Scanner<R> {
        fn read<T: FromStr>(&mut self) -> T {
            loop {
                if let Some(token) = self.token_iter.next() {
                    return token.parse().ok().expect("Failed to parse");
                }

                self.buf.clear();
                self.reader.read_until(b'\n', &mut self.buf).unwrap();
                self.token_iter = unsafe {
                    std::mem::transmute(
                        str::from_utf8_unchecked(&self.buf).split_ascii_whitespace(),
                    )
                }
            }
        }
    }

    const DEFAULT_BUF_SIZE: usize = 8192 * 16;

    pub fn buf_stdin() -> BufReader<StdinLock<'static>> {
        BufReader::with_capacity(DEFAULT_BUF_SIZE, stdin().lock())
    }

    pub fn buf_stdout() -> BufWriter<StdoutLock<'static>> {
        BufWriter::with_capacity(DEFAULT_BUF_SIZE, stdout().lock())
    }

    thread_local! {
        pub static __STDOUT: RefCell<BufWriter<std::io::StdoutLock<'static>>> = RefCell::new(buf_stdout());
    }

    #[macro_export]
    macro_rules! cout {
        ($($arg:tt)*) => {
            use std::io::Write;

            $crate::prelude::__STDOUT.with(|stdout| {
                write!(stdout.borrow_mut(), $($arg)*).unwrap();
            })
        };
    }

    #[macro_export]
    macro_rules! coutln {
        ($($arg:tt)*) => {
            use std::io::Write;

            $crate::prelude::__STDOUT.with(|stdout| {
                writeln!(stdout.borrow_mut(), $($arg)*).unwrap();
            })
        };
    }
}
```