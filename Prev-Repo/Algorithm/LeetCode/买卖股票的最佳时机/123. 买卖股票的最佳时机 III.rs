#![allow(unused)]

use std::i32;

struct Solution;

// 构建一个状态机
impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let n = prices.len();
        let mut f = vec![[0; 4]; n + 1];

        f[0].fill(i32::MIN / 2);

        for (i, &p) in prices.iter().enumerate() {
            f[i + 1][0] = f[i][0].max(-p);
            f[i + 1][1] = f[i][1].max(f[i][0] + p);
            f[i + 1][2] = f[i][2].max(f[i][1] - p);
            f[i + 1][3] = f[i][3].max(f[i][2] + p);
        }

        f[n][3].max(f[n][1]).max(0)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_max_profit() {
        let prices = vec![3, 3, 5, 0, 0, 3, 1, 4];
        assert_eq!(Solution::max_profit(prices), 6);

        let prices = vec![1, 2, 3, 4, 5];
        assert_eq!(Solution::max_profit(prices), 4);

        let prices = vec![7, 6, 4, 3, 1];
        assert_eq!(Solution::max_profit(prices), 0);

        let prices = vec![1];
        assert_eq!(Solution::max_profit(prices), 0);
    }
}

fn main() {}
