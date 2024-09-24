#pragma once

#include "cassert"
#include "mysql/mysql.h"
#include "SqlConnectPool.hpp"

namespace Koro {
    
class SqlConnect {
private:
    MYSQL *sql_;
    SqlConnectPool *pool_;

public:
    explicit SqlConnect(MYSQL **sql, SqlConnectPool *pool) {
        assert(pool);
        sql_ = pool->GetConnect();
        *sql = sql_;
        pool_ = pool;
    }
    ~SqlConnect() {
        if (sql_) {
            pool_->ReleaseConnect(sql_);
        }
    }
};


}
