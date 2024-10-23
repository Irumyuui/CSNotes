use std::{
    net::{IpAddr, SocketAddr},
    ops::Deref,
    sync::Arc,
    time::Duration,
};

use anyhow::Result;
use axum::{
    extract::{Request, State},
    http::StatusCode,
    middleware::{self, Next},
    response::IntoResponse,
    routing::get,
    Router,
};
use axum_client_ip::{SecureClientIp, SecureClientIpSource};
use timedmap::TimedMap;
use tracing_subscriber::{layer::SubscriberExt, util::SubscriberInitExt};

#[derive(Debug)]
struct RateLimiter {
    inner: TimedMap<IpAddr, i32>,
}

impl Deref for RateLimiter {
    type Target = TimedMap<IpAddr, i32>;

    fn deref(&self) -> &Self::Target {
        &self.inner
    }
}

impl RateLimiter {
    pub fn new() -> Self {
        Self {
            inner: Default::default(),
        }
    }

    pub fn check(&self, ip_addr: &IpAddr) -> bool {
        let count = self.get(ip_addr).unwrap_or(0);
        if count > 10 {
            false
        } else {
            self.insert(ip_addr.clone(), count + 1, Duration::from_secs(6));
            true
        }
    }
}

#[derive(Debug, Clone)]
struct LimitState {
    inner: Arc<RateLimiter>,
}

impl Deref for LimitState {
    type Target = Arc<RateLimiter>;

    fn deref(&self) -> &Self::Target {
        &self.inner
    }
}

impl LimitState {
    pub fn new() -> Self {
        Self {
            inner: Arc::new(RateLimiter::new()),
        }
    }
}

async fn rate_limit_midleware(
    State(state): State<LimitState>,
    SecureClientIp(ip_addr): SecureClientIp,
    req: Request,
    next: Next,
) -> impl IntoResponse {
    // tracing::debug!("Get client addr: {}", ip_addr);

    if state.check(&ip_addr) {
        next.run(req).await
    } else {
        (StatusCode::TOO_MANY_REQUESTS, "Too many request!").into_response()
    }
}

async fn say_hello_handler(SecureClientIp(ip_addr): SecureClientIp) -> String {
    format!("Hello: {}", ip_addr)
}

#[tokio::main]
async fn main() -> Result<()> {
    tracing_subscriber::registry()
        .with(tracing_subscriber::fmt::layer())
        .init();

    let state = LimitState::new();
    let app = Router::new()
        .route("/hello", get(say_hello_handler))
        .route_layer(middleware::from_fn_with_state(state, rate_limit_midleware))
        .layer(SecureClientIpSource::ConnectInfo.into_extension());

    let listener = tokio::net::TcpListener::bind("0.0.0.0:8080").await?;

    let addr = listener.local_addr()?;
    tracing::info!("Listenning on: {}", addr);

    axum::serve(
        listener,
        app.into_make_service_with_connect_info::<SocketAddr>(),
    )
    .await?;

    Ok(())
}
