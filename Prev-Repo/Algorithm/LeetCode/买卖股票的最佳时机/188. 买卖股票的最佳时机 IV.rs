#![allow(unused)]

use std::i32;

struct Solution;

// 状态机
impl Solution {
    pub fn max_profit(k: i32, prices: Vec<i32>) -> i32 {
        let k = k as usize * 2;
        let mut f = vec![i32::MIN / 2; k];

        for &x in prices.iter() {
            f[0] = f[0].max(-x);
            for i in 1..k {
                f[i] = f[i].max(f[i - 1] + if i % 2 == 1 { x } else { -x })
            }
        }

        (*f.iter().max().unwrap()).max(0)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_max_profit() {
        let k = 2;
        let prices = vec![2, 4, 1];
        assert_eq!(Solution::max_profit(k, prices), 2);

        let k = 2;
        let prices = vec![3, 2, 6, 5, 0, 3];
        assert_eq!(Solution::max_profit(k, prices), 7);
    }
}

fn main() {}
