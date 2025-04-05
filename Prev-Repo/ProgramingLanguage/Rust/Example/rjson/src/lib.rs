use std::collections::HashMap;

#[derive(Clone, Debug, PartialEq)]
pub enum Json {
    Null,
    Bool(bool),
    Number(f64),
    String(String),
    Array(Vec<Json>),
    Object(HashMap<String, Json>),
}

impl From<bool> for Json {
    fn from(value: bool) -> Self {
        Json::Bool(value)
    }
}

impl From<&str> for Json {
    fn from(value: &str) -> Self {
        Json::String(value.to_string())
    }
}

impl From<String> for Json {
    fn from(value: String) -> Self {
        Json::String(value)
    }
}

macro_rules! json_impl_number_from {
    (  $( $type: ty )* ) => {
        $(
            impl From<$type> for Json {
                fn from(value: $type) -> Self {
                    Json::Number(value as f64)
                }
            }
        )*
    }
}

json_impl_number_from!(i8 i16 i32 i64 isize u8 u16 u32 u64 usize f32 f64);

#[macro_export]
macro_rules! json {
    (null) => {
        Json::Null
    };

    ([ $( $item: tt ), * ]) => {
        Json::Array(vec![ $( json!($item) ), * ])
    };

    ({ $( $key: tt : $value: tt ), * }) => {
        Json::Object(std::collections::HashMap::from([
            $(
                ( $key.to_string(), json!($value) )
            ), *
        ]))
    };

    ($value: tt) => {
        Json::from($value)
    };
}
