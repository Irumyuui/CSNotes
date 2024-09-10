use std::{
    ops::{Add, AddAssign},
    process::Output,
};

pub struct FenwickTree<T: Copy> {
    data: Vec<T>,
}

impl<T: Copy> FenwickTree<T> {
    pub fn new(n: usize, init_val: T) -> Self {
        Self {
            data: vec![init_val; n],
        }
    }

    pub fn add(&mut self, mut p: usize, val: T)
    where
        T: Add<Output = T> + AddAssign,
    {
        p += 1;
        while p <= self.data.len() {
            self.data[p - 1] += val;
            p += p & (!p + 1);
        }
    }

    pub fn sum(&self, mut p: usize, mut init_val: T) -> T
    where
        T: Add<Output = T> + AddAssign,
    {
        p += 1;
        while p > 0 {
            init_val += self.data[p - 1];
            p -= p & (!p + 1);
        }

        init_val
    }
}