#![allow(unused)]

struct Solution;

impl Solution {
    // 倒着找一个最小卖出值就好
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let mut mx = prices.last().unwrap();
        let mut ans = 0;
        for p in prices.iter().rev() {
            ans = ans.max(mx - p);
            mx = mx.max(p);
        }
        ans
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_max_profit() {
        let prices = vec![7, 1, 5, 3, 6, 4];
        assert_eq!(Solution::max_profit(prices), 5);

        let prices = vec![7, 6, 4, 3, 1];
        assert_eq!(Solution::max_profit(prices), 0);
    }
}

fn main() {}
