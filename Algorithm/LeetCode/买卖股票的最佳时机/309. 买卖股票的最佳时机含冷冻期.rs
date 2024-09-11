#![allow(unused)]

struct Solution;

// 状态机
impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let n = prices.len();
        let mut f = [0, i32::MIN / 2, i32::MIN / 2];

        for &p in prices.iter() {
            let mut ft = [0, i32::MIN / 2, i32::MIN / 2];
            ft[1] = f[1].max(f[0] - p);
            ft[2] = f[2].max(f[1] + p);
            ft[0] = f[0].max(f[2]);
            std::mem::swap(&mut f, &mut ft);
        }

        f[0].max(f[2]).max(0)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
        let prices = vec![1, 2, 3, 0, 2];
        assert_eq!(Solution::max_profit(prices), 3);
    }

    #[test]
    fn test2() {
        let prices = vec![1];
        assert_eq!(Solution::max_profit(prices), 0);
    }
}

fn main() {}
