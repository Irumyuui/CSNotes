use rjson::{json, Json};

fn main() {
    let json = json!({
        "name": "Alice",
        "age": 30,
        "is_student": false,
        "courses": ["Math", "Science"],
        "address": {
            "street": "123 Elm St",
            "city": "Springfield"
        }
    });

    println!("{:?}", json);
}
