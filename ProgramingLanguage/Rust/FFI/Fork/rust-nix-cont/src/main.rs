use nix::libc::{exit, fork, getpid};

fn main() {
    let result = unsafe { fork() };

    if result < 0 {
        eprintln!("Error forking process.");
        unsafe { exit(-1) };
    }

    if result == 0 {
        println!("Child process get: {}", unsafe { getpid() });
    } else {
        println!("Parent processg get: {}", result);
    }
}
