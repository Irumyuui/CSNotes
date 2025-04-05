use std::error::Error;
use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};
use std::thread;

fn main() -> std::io::Result<()> {
    let listener = TcpListener::bind("::1:11451")?;
    let mut threads: Vec<thread::JoinHandle<()>> = vec![];

    for stream in listener.incoming() {
        let stream = stream?;
        let handle = thread::spawn(move || {
            handle_client(stream).unwrap_or_else(|error| eprintln!("{:?}", error))
        });
        threads.push(handle);
    }

    for thread in threads {
        thread.join().unwrap();
    }

    Ok(())
}

fn handle_client(mut stream: TcpStream) -> Result<(), Box<dyn Error>> {
    let mut buffer = [0; 1024];

    for _ in 0..1000 {
        let bytes_read = stream.read(&mut buffer)?;
        if bytes_read == 0 {
            return Ok(());
        }

        stream.write(&buffer[..bytes_read])?;
        thread::sleep(std::time::Duration::from_secs(1));
    }

    Ok(())
}
