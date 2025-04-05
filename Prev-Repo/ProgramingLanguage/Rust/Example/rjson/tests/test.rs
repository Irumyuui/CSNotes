#[cfg(test)]
mod tests {
    use rjson::{json, Json};

    #[test]
    fn test_parse_null() {
        let json = json!(null);
        assert_eq!(json, Json::Null);
    }

    #[test]
    fn test_parse_number() {
        let json = json!(114.514);
        assert_eq!(json, Json::Number(114.514));
    }

    #[test]
    fn test_parse_bool() {
        assert_eq!(json!(true), Json::Bool(true));
        assert_eq!(json!(false), Json::Bool(false));
    }

    #[test]
    fn test_parse_string() {
        assert_eq!(json!("str"), Json::String("str".to_string()));
    }

    #[test]
    fn test_parse_array() {
        let json = json!([114.514, "string", null, true]);

        assert_eq!(
            json,
            Json::Array(vec![
                Json::Number(114.514),
                Json::String("string".to_string()),
                Json::Null,
                Json::Bool(true)
            ])
        );
    }

    #[test]
    fn test_parse_object() {
        let json = json!({
            "name": null,
            "age": 25,
            "is_student": true,
            "hobbies": ["reading", "swimming", "running"]
        });

        assert_eq!(
            json,
            Json::Object(std::collections::HashMap::from([
                ("name".to_string(), Json::Null),
                ("age".to_string(), Json::Number(25.0)),
                ("is_student".to_string(), Json::Bool(true)),
                (
                    "hobbies".to_string(),
                    Json::Array(vec![
                        Json::String("reading".to_string()),
                        Json::String("swimming".to_string()),
                        Json::String("running".to_string())
                    ])
                )
            ]))
        );
    }
}
