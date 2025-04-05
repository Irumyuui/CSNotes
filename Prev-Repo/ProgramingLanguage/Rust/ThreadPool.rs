use std::sync::{Arc, Mutex};

type Job = Box<dyn FnOnce() + Send + 'static>;

enum Task {
    Job(Job),
    End,
}

pub struct ThreadPool {
    workers: Vec<std::thread::JoinHandle<()>>,
    tasks: std::sync::mpsc::Sender<Task>,
}

impl ThreadPool {
    pub fn new(thread_count: usize) -> Option<Self> {
        if thread_count == 0 {
            return None;
        }

        let (sender, receiver) = std::sync::mpsc::channel();
        let mut workers = Vec::with_capacity(thread_count);

        let receiver = Arc::new(Mutex::new(receiver));

        for _ in 0..thread_count {
            let receiver = receiver.clone();
            workers.push(std::thread::spawn(move || loop {
                match receiver.lock().unwrap().recv().unwrap() {
                    Task::Job(job) => {
                        job();
                    }
                    Task::End => {
                        eprintln!("Pool shutting down.");
                        break;
                    }
                }
            }));
        }

        Some(Self {
            workers,
            tasks: sender,
        })
    }

    pub fn execute<F>(&self, job: F)
    where
        F: FnOnce() + Send + 'static,
    {
        let job = Task::Job(Box::new(job));
        self.tasks.send(job).unwrap();
    }
}

impl Drop for ThreadPool {
    fn drop(&mut self) {
        for _ in 0..self.workers.len() {
            self.tasks.send(Task::End).unwrap();
        }

        for worker in self.workers.drain(..) {
            worker.join().unwrap();
        }

        eprintln!("Pool dropped.")
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn it_works() {
        let p = ThreadPool::new(4);
        assert!(p.is_some());

        let p = p.unwrap();
        p.execute(|| println!("do new job1"));
        p.execute(|| println!("do new job2"));
        p.execute(|| println!("do new job3"));
        p.execute(|| println!("do new job4"));
    }
}

fn main() {
    let p = ThreadPool::new(4).unwrap();
    p.execute(|| println!("do new job1"));
    p.execute(|| println!("do new job2"));
    p.execute(|| println!("do new job3"));
    p.execute(|| println!("do new job4"));
}
