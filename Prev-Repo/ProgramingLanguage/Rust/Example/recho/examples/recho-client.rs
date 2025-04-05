use std::{
    io::{stdin, BufRead, BufReader, Write},
    net::TcpStream,
};

fn main() -> std::io::Result<()> {
    let mut stream = TcpStream::connect("::1:11451")?;

    loop {
        let mut input = String::new();
        stdin().read_line(&mut input)?;

        if input.trim() == "exit" {
            break;
        }

        stream.write(input.as_bytes())?;
        let mut reader = BufReader::new(&stream);
        let mut buf: Vec<u8> = vec![];
        reader.read_until(b'\n', &mut buf)?;

        let result = String::from_utf8(buf).expect("Invalid UTF-8");
        println!("Server: {}", result);
    }

    Ok(())
}
