use std::time::Duration;

use tokio::{signal::unix::SignalKind, time::sleep};

const GRACEFUL_SHUTDOWN_TIMEOUT: u64 = 30;

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut sigterm = tokio::signal::unix::signal(SignalKind::terminate())?;
    let mut sigint = tokio::signal::unix::signal(SignalKind::interrupt())?;

    tokio::select! {
        _ = sigterm.recv() => {
            println!("Received SIGTERM, shutting down gracefully...");
        }
        _ = sigint.recv() => {
            println!("Received SIGINT, shutting down gracefully...");
        }
    }

    // 执行优雅停机任务
    let graceful_shutdown_task = tokio::task::spawn_blocking(|| {
        cleanup();
    });

    // 等待请求处理完成
    let start_time = std::time::Instant::now();
    while start_time.elapsed().as_secs() < GRACEFUL_SHUTDOWN_TIMEOUT {
        if is_all_request_completed() {
            break;
        }
        sleep(Duration::from_secs(1)).await;
    }

    // 等待优雅停机任务完成
    graceful_shutdown_task.await.unwrap();

    // 如果请求还没有处理完成，则直接关闭服务器
    if !is_all_request_completed() {
        println!("Graceful shutdown timeout, closing server...");
    }

    Ok(())
}

fn is_all_request_completed() -> bool {
    true
}

fn cleanup() {
    println!("Cleaning up...");
    std::thread::sleep(std::time::Duration::from_secs(5));
    println!("Clean done.");
}
