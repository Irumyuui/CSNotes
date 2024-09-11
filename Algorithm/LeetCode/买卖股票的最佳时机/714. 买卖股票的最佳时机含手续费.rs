#![allow(unused)]

struct Solution;

impl Solution {
    pub fn max_profit(prices: Vec<i32>, fee: i32) -> i32 {
        let mut f = [0, i32::MIN / 2];
        for &p in prices.iter() {
            let mut ft = [0, i32::MIN / 2];
            ft[1] = f[1].max(f[0] - p - fee);
            ft[0] = f[0].max(f[1] + p);
            std::mem::swap(&mut ft, &mut f);
        }
        f[0].max(0)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
        let prices = vec![1, 3, 2, 8, 4, 9];
        let fee = 2;
        assert_eq!(Solution::max_profit(prices, fee), 8);
    }

    #[test]
    fn test2() {
        let prices = vec![1, 3, 7, 5, 10, 3];
        let fee = 3;
        assert_eq!(Solution::max_profit(prices, fee), 6);
    }
}

fn main() {}
