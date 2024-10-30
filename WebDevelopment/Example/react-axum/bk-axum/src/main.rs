use axum::{routing, Router};
use tokio::net::TcpListener;
use tower_http::cors::{Any, CorsLayer};
use tracing_subscriber::{fmt, layer::SubscriberExt, util::SubscriberInitExt};

#[tokio::main]
async fn main() {
    tracing_subscriber::registry().with(fmt::layer()).init();

    let cors = CorsLayer::new().allow_origin(Any);
    let app = Router::new()
        .route("/", routing::get(|| async { 
            tracing::info!("Action!");
            "From Axum."
        }))
        .layer(cors);

    let listener = TcpListener::bind("localhost:8080").await.unwrap();
    axum::serve(listener, app.into_make_service())
        .await
        .unwrap();
}
