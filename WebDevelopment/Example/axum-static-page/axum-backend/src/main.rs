use axum::{
    http::StatusCode,
    routing::{get, get_service},
    Json, Router, ServiceExt,
};
use serde_json::json;
use std::net::SocketAddr;
use tokio::net::TcpListener;
use tower_http::{services::ServeDir, trace::TraceLayer};
use tracing_subscriber::{layer::SubscriberExt, util::SubscriberInitExt};

#[tokio::main]
async fn main() -> anyhow::Result<()> {
    if std::env::var_os("RUST_LOG").is_none() {
        std::env::set_var(
            "RUST_LOG",
            "example_static_file_server=debug,tower_http=debug",
        )
    }

    tracing_subscriber::registry()
        .with(tracing_subscriber::fmt::layer())
        .init();

    let app = Router::new()
        .nest_service(
            "/",
            ServeDir::new("dist").not_found_service(ServeDir::new("dist/index.html")),
        )
        .route("/api/hello", get(|| async { "Hello, World!" }))
        .fallback(|| async {
            Json(json!({
                "status": "Not Found",
                "message": "Page not found"
            }))
        })
        .layer(TraceLayer::new_for_http());

    let addr = SocketAddr::from(([127, 0, 0, 1], 3000));
    let listener = TcpListener::bind(&addr).await?;

    tracing::info!("listening on http://{}", addr);

    axum::serve(listener, app).await?;

    Ok(())
}
