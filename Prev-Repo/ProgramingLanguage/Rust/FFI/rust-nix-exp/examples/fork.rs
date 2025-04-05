use std::process::exit;

use nix::{
    sys::wait::waitpid,
    unistd::{fork, write, ForkResult},
};

fn main() {
    match unsafe { fork() } {
        Ok(ForkResult::Parent { child, .. }) => {
            println!(
                "Continuing execution in parent process, new child has pid: {}",
                child
            );
            waitpid(child, None).unwrap();
        }
        Ok(ForkResult::Child) => {
            write(std::io::stdout(), "I'm a new child process\n".as_bytes()).ok();
            exit(0);
        }
        Err(_) => println!("Fork failed"),
    }
}
