考虑 $lcm(x, y) = x'y'gcd(x,y)$ 。

不妨设 $x' = \cfrac{x}{gcd(x, y)}, y' = \cfrac{y}{gcd(x, y)}$ 。

考虑当 $lcm(x, y)$ 是半质数时，说明其只能分解出两个质数因数，因此 $x', y', gcd(x, y)$ 中一定有一个为 $1$ 。

如果是 $gcd(x, y) = 1$ ，那么说明 $lcm(x, y) = \cfrac{x y}{gcd(x, y)} = x y = x' y'$ ，又因为我们的假设，得到 $x = x', y = 'y$ ，其实这里就意味着 $x, y$ 互质的同时， 是两个质数，并且 $x \ne y$ 。

如果设 $'x = 1$ ，则需要 $y', x, gcd(x, y)$ 都是质数， 那么 $x = gcx(x, y)$，则 $y = y' gcd(x, y) = xy'$ ，也就是说 $y$ 是一个半质数，要求 $x$ 是 $y$ 的一个因子。

如果 $'x = 'y = 1$ ，可以吗？可以的，考虑 $lcm(4, 4) = 4 = 2 \times 2$ ，满足。 

```rust
use std::collections::HashMap;

use crate::prelude::*;

fn main() {
    #[allow(unused)]
    let mut scan = Scanner::new(buf_stdin());

    const N: usize = 200_010;
    let mut is_prime = vec![true; N];
    let mut prime = vec![];
    let mut pcnt = vec![0; N];
    let mut dv = vec![0; N];
    is_prime[0] = false;
    is_prime[1] = false;
    for i in 2..N {
        if is_prime[i] {
            prime.push(i);
            pcnt[i] = 1;
            dv[i] = i;
        }
        for &p in &prime {
            if i * p >= N {
                break;
            }
            is_prime[i * p] = false;
            dv[i * p] = p;
            pcnt[i * p] = pcnt[i] + 1;
            if i % p == 0 {
                break;
            }
        }
    }

    let case = scan.read();
    for _ in 0..case {
        let n: usize = scan.read();
        let a: Vec<usize> = (0..n).map(|_| scan.read()).collect();

        let mut ans: u64 = 0;
        let mut mp1 = HashMap::new();
        let mut cnt = 0;
        let mut mp2 = HashMap::new();

        for &x in a.iter() {
            match pcnt[x] {
                1 => {
                    let e = mp1.entry(x).or_insert(0);
                    *e += 1;
                    cnt += 1;
                    ans += cnt - *e;
                }
                2 => {
                    let e = mp2.entry(x).or_insert(0);
                    *e += 1;
                    ans += *e;
                }
                _ => {}
            }
        }

        eprintln!("{}", ans);

        for (p, q) in a.iter().filter_map(|&x| {
            if pcnt[x] == 2 {
                Some((dv[x], x / dv[x]))
            } else {
                None
            }
        }) {
            ans += mp1.get(&p).copied().unwrap_or_default()
                + (p != q).select(mp1.get(&q).copied().unwrap_or_default(), 0);
        }

        coutln!("{}", ans);
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