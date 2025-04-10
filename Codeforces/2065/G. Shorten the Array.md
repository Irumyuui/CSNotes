TAG：位运算，字典树。

首先思考一个问题：我们想找到两个数字 $a,b$ ，满足 $a \oplus b=k$ ，要怎么做？因为异或操作本身是可以换过去的，所以我们可以得到 $b=a \oplus k$ ，那么一个很自然的思想，枚举 $a$ ，倒推 $b$ 。

但这里我们是需要要求 $a \oplus b \ge k$ ，从位上的角度来说，我们就需要找到 $a,k$ 在对应第 $i$ 位中的情况了。

- 如果 $k_i=0$ ，那么我们其实任选 $0$ 或者 $1$ ；
- 如果 $k_i=1$ ，那么 $ai \oplus bi=1$ ;

那么，什么东西能够方便我们在枚举位的同时，方便我们找呢？答案是字典树，按位建即可。

- $k_i=0$ 时，任选 $0$ 和 $1$ ，但是因为选的时候一个是绝对最大一个是依然满足搜索前缀，因此还需要接着按 $a_i$ 找；
- $k_i = 1$ 时，那么只能找一个与 $a_i$ 抵消的了；

因为需要计算的是最大值，那么按照上面搜索至少大于或等于 $k$ 的逻辑，插入字典树的同时更新每个节点的最大可到达位置即可，因为搜索肯定是走前缀的。

```rust
use crate::prelude::*;

fn main() {
    #[allow(unused)]
    let mut scan = Scanner::new(buf_stdin());

    let case: usize = scan.read();
    #[allow(unused)]
    'main: for _ in 0..case {
        let n: usize = scan.read();
        let k: u32 = scan.read();
        let arr: Vec<u32> = (0..n).map(|_| scan.read()).collect();

        let mut ans = usize::MAX;
        let mut trie = Trie::new();
        for (i, e) in arr.into_iter().enumerate() {
            trie.insert(e, i);
            if let Some(pos) = trie.find(e, k) {
                ans = ans.min(i - pos + 1);
            }
        }

        if ans == usize::MAX {
            coutln!("-1");
        } else {
            coutln!("{}", ans);
        }
    }
}

#[derive(Debug)]
struct Node {
    child: [usize; 2],
    pos: Option<usize>,
}

pub struct Trie {
    nodes: Vec<Node>,
}

impl Trie {
    pub fn new() -> Self {
        Self {
            nodes: vec![Node {
                child: [usize::MAX, usize::MAX],
                pos: None,
            }],
        }
    }

    pub fn insert(&mut self, x: u32, pos: usize) {
        let mut cur = 0;
        for i in (0..32).rev() {
            let bit = ((x >> i) & 1) as usize;
            if self.nodes[cur].child[bit] == usize::MAX {
                self.nodes.push(Node {
                    child: [usize::MAX, usize::MAX],
                    pos: None,
                });
                self.nodes[cur].child[bit] = self.nodes.len() - 1;
            }
            cur = self.nodes[cur].child[bit];
            self.nodes[cur].pos.replace(pos);
        }
    }

    pub fn find(&self, x: u32, k: u32) -> Option<usize> {
        let mut cur = 0;
        let mut res = None;
        for i in (0..32).rev() {
            let xbit = ((x >> i) & 1) as usize;
            let kbit = ((k >> i) & 1) as usize;

            cur = if kbit == 0 {
                let other = self.nodes[cur].child[xbit ^ 1];
                if other != usize::MAX {
                    res = res.max(self.nodes[other].pos);
                }
                self.nodes[cur].child[xbit]
            } else {
                self.nodes[cur].child[xbit ^ 1]
            };

            if cur == usize::MAX {
                return res;
            }
        }

        res.max(self.nodes[cur].pos)
    }
}

impl Default for Trie {
    fn default() -> Self {
        Self::new()
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

    const DEFAULT_BUF_SIZE: usize = 8192;

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