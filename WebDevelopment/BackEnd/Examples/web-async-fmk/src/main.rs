use tokio::net::TcpListener;

#[tokio::main]
async fn main() -> web_async_fmk::Result<()> {
    init_logging()?;

    web_async_fmk::server::run(
        TcpListener::bind("127.0.0.1:8080").await?,
        tokio::signal::ctrl_c(),
    )
    .await;

    Ok(())
}

#[allow(unused)]
fn init_logging() -> web_async_fmk::Result<()> {
    Ok(())
}
