use tokio::signal::unix::SignalKind;

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    // 创建信号监听器
    let mut sigterm = tokio::signal::unix::signal(SignalKind::terminate())?;
    let mut sigint = tokio::signal::unix::signal(SignalKind::interrupt())?;

    // 等待信号
    tokio::select! {
        _ = sigterm.recv() => {
            println!("Received SIGTERM, shutting down gracefully...");
        }
        _ = sigint.recv() => {
            println!("Received SIGINT, shutting down gracefully...");
        }
    }

    Ok(())
}
