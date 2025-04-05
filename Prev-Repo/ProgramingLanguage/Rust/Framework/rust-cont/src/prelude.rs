pub use crate::error::Error;

pub type Result<T> = std::result::Result<T, Error>;

pub struct Wapper<T>(pub T);
