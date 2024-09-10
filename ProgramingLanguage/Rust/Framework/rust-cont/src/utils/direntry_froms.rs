use std::fs::DirEntry;

use crate::prelude::*;

// 一种扩展方法的实现
impl TryFrom<Wapper<&DirEntry>> for String {
    type Error = Error;

    fn try_from(value: Wapper<&DirEntry>) -> std::result::Result<Self, Self::Error> {
        value
            .0
            .path()
            .to_str()
            .map(String::from)
            .ok_or_else(|| Error::Generic(format!("Invalid path: {:?}", value.0)))
    }
}
