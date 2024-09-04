use crossbeam_channel;
use std::{thread, time};

fn parallel_map<T, U, F>(mut input_vec: Vec<T>, num_threads: usize, f: F) -> Vec<U>
where
    F: FnOnce(T) -> U + Send + Copy + 'static,
    T: Send + 'static,
    U: Send + 'static + Default,
{
    let mut output_vec: Vec<U> = Vec::with_capacity(input_vec.len());
    // TODO: implement parallel map!

    let num_threads = usize::min(input_vec.len(), num_threads);

    if num_threads <= 1 {
        while let Some(item) = input_vec.pop() {
            output_vec.push(f(item));
        }
        return output_vec;
    }

    let (in_s, in_r) = crossbeam_channel::unbounded();
    let (out_s, out_r) = crossbeam_channel::unbounded();

    let mut threads = vec![];

    for _ in 0..num_threads {
        let in_r = in_r.clone();
        let out_s = out_s.clone();

        threads.push(thread::spawn(move || {
            while let Ok((item, index)) = in_r.recv() {
                out_s.send((f(item), index)).expect("Failed to send result");
            }
        }));
    }
    drop(out_s);

    for (index, item) in input_vec.into_iter().enumerate() {
        in_s.send((item, index)).expect("Failed to send item");
    }
    drop(in_s);

    let mut unordered_result = Vec::with_capacity(output_vec.capacity());
    let mut index_map = vec![0; output_vec.capacity()];
    while let Ok((result, index)) = out_r.recv() {
        index_map[index] = unordered_result.len();
        unordered_result.push(Some(result));
    }

    for i in 0..output_vec.capacity() {
        output_vec.push(unordered_result[index_map[i]].take().unwrap())
    }

    for thread in threads.drain(..) {
        thread.join().expect("Failed to join thread");
    }

    output_vec
}

fn main() {
    let v = vec![6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 12, 18, 11, 5, 20];
    let squares = parallel_map(v, 10, |num| {
        println!("{} squared is {}", num, num * num);
        thread::sleep(time::Duration::from_millis(500));
        num * num
    });
    println!("squares: {:?}", squares);
}
