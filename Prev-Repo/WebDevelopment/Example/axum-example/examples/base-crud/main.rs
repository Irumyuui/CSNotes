use anyhow::Result;
use axum::{http::StatusCode, response::IntoResponse, routing, Router};
use handler::tickets::api_router;
use tracing_subscriber::{layer::SubscriberExt, util::SubscriberInitExt};

pub mod handler;

#[tokio::main]
async fn main() -> Result<()> {
    tracing_subscriber::registry()
        .with(tracing_subscriber::fmt::layer())
        .init();

    let addr = "localhost:8080";
    let listener = tokio::net::TcpListener::bind(addr).await?;

    let app = Router::new()
        .route("/", routing::get(root_handler))
        .nest("/api", api_router())
        .fallback(routing::get(|| async { "404 NOTFOUND" }));

    let addr = listener.local_addr()?;
    tracing::info!("Listening on: http://{}", addr);

    axum::serve(listener, app).await?;

    Ok(())
}

async fn root_handler() -> impl IntoResponse {
    StatusCode::OK
}

#[allow(unused)]
#[derive(Debug)]
pub struct User {
    id: u64,
    name: String,
}
