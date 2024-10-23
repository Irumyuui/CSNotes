#![allow(unused)]

use axum::{extract::Path, response::IntoResponse, routing, Json, Router};
use serde::Deserialize;

pub fn api_router() -> Router {
    Router::new()
        .route("/tickets/:id", routing::get(get_handler))
        .route("/tickets", routing::post(create_handler))
        .route("/tickets/:id", routing::patch(update_handler))
        .route("/tickets/:id", routing::delete(delete_handler))
        .route("/tickets", routing::get(list_handler))
}

#[derive(Debug, Deserialize)]
pub struct CrateTicketRequest {
    title: String,
    description: String,
    status: u8,
}

async fn create_handler(Json(req): Json<CrateTicketRequest>) -> impl IntoResponse {
    tracing::debug!("create_handler req: {:#?}", req)
}

#[derive(Debug, Deserialize)]
pub struct UpdateTicketRequest {
    title: String,
    description: String,
    status: u8,
}

async fn update_handler(
    Path(ticket_id): Path<u64>,
    Json(req): Json<UpdateTicketRequest>,
) -> impl IntoResponse {
    tracing::debug!("update_handler ticket_id: {:#?}", ticket_id);
    tracing::debug!("update_handler req: {:#?}", req);
    Json("Update")
}

async fn delete_handler() -> impl IntoResponse {
    Json("Delete")
}

async fn get_handler(Path(ticket_id): Path<u64>) -> impl IntoResponse {
    tracing::debug!("get_handler ticket_id: {:#?}", ticket_id)
}

async fn list_handler() -> impl IntoResponse {
    Json("Get List")
}
