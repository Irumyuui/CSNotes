use tokio::signal::unix::{signal, SignalKind};

#[allow(unused)]
const GRACEFUL_SHUTDOWN_TIMEOUT: u64 = 30;

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut sigterm = signal(SignalKind::terminate())?;
    let mut sigint = signal(SignalKind::interrupt())?;

    tokio::select! {
        _ = sigterm.recv() => {
            println!("Received SIGTERM, shutting down gracefully...");
        }
        _ = sigint.recv() => {
            println!("Received SIGINT, shutting down gracefully...");
        }
    }

    let start_time = std::time::Instant::now();
    while start_time.elapsed().as_secs() < GRACEFUL_SHUTDOWN_TIMEOUT {
        if is_all_request_complete() {
            break;
        }
        tokio::time::sleep(std::time::Duration::from_secs(1)).await;
    }

    if !is_all_request_complete() {
        println!("Graceful shutdown timed out, force shutting down...")
    }

    Ok(())
}

const fn is_all_request_complete() -> bool {
    true
}
