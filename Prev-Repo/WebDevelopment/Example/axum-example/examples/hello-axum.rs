use anyhow::Result;
use axum::{response::IntoResponse, routing, Router};
use tracing_subscriber::{layer::SubscriberExt, util::SubscriberInitExt};

#[tokio::main]
async fn main() -> Result<()> {
    tracing_subscriber::registry()
        .with(tracing_subscriber::fmt::layer())
        .init();

    let addr = "localhost:8080";
    let listener = tokio::net::TcpListener::bind(addr).await?;

    let app = Router::new()
        .route("/", routing::get(root_handler))
        .fallback(routing::get(|| async { "404 NOTFOUND" }));

    let addr = listener.local_addr()?;
    tracing::info!("Listening on: http://{}", addr);

    axum::serve(listener, app).await?;

    Ok(())
}

async fn root_handler() -> impl IntoResponse {
    "Hello axum!"
}
