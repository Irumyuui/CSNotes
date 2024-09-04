use tokio::io::{AsyncReadExt, AsyncWriteExt};

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let listener = tokio::net::TcpListener::bind("::1:11451").await?;

    loop {
        let (mut socket, _) = listener.accept().await?;

        tokio::spawn(async move {
            let mut buf = [0; 1024];

            loop {
                let n = match socket.read(&mut buf).await {
                    Ok(n) if n == 0 => return,
                    Ok(n) => n,
                    Err(e) => {
                        eprintln!("Faild to read from socket: {:?}", e);
                        return;
                    }
                };

                if let Err(e) = socket.write_all(&buf[..n]).await {
                    eprintln!("Failed to write to socket: {:?}", e);
                    return;
                }
            }
        });
    }
}
