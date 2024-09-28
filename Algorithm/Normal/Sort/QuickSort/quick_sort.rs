pub fn quick_sort_parition<T: Ord>(arr: &mut [T]) -> usize {
    let pivot = arr.len() - 1;
    let mut i = 0;
    for j in 0..pivot {
        if arr[j] <= arr[pivot] {
            arr.swap(i, j);
            i += 1;
        }
    }
    arr.swap(i, pivot);
    i
}

pub fn quick_sort<T: Ord>(arr: &mut [T]) {
    if arr.len() <= 1 {
        return;
    }

    let pivot = quick_sort_parition(arr);
    quick_sort(&mut arr[..pivot]);
    quick_sort(&mut arr[pivot + 1..]);
}

fn main() {
    let mut arr = [5, 3, 8, 4, 2];
    quick_sort(&mut arr);
    println!("{:?}", arr);
}
