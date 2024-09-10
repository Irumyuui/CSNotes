// #![allow(unused)]

mod error;
mod prelude;
mod utils;

use std::fs::read_dir;

use prelude::Wapper;

fn main() -> prelude::Result<()> {
    for entry in read_dir("./")?.filter_map(|e| e.ok()) {
        let entry: String = Wapper(&entry).try_into()?;
        println!("{entry:?}");
    }

    Ok(())
}
