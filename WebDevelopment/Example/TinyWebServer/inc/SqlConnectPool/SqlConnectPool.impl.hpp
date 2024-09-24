#pragma once

#include "SqlConnectPool.decl.hpp"
#include "log/Log.decl.Hpp"
#include <cassert>
#include <exception>
#include <memory>
#include <mutex>
#include <mysql/mysql.h>
#include <string_view>

namespace Koro {

inline SqlConnectPool::SqlConnectPool()
 : use_count_(0), free_count_(0) {

}

inline SqlConnectPool::~SqlConnectPool() {
    Destroy();
}

inline void SqlConnectPool::Init(this SqlConnectPool &self,
              std::string_view host, int port,
              std::string_view user, std::string_view pwd,
              std::string_view db_name, int max_connect_count) {
    assert(max_connect_count > 0);
    for (int i = 0; i < max_connect_count; i ++) {
        MYSQL *sql = nullptr;
        sql = mysql_init(sql);
        if (!sql) {
            ToLog<LogLevel::Error>(MakeLogMessage("MySQL init error"));
            // assert(sql);
            std::terminate();
        }
        sql = mysql_real_connect(sql, host.data(), user.data(), pwd.data(), db_name.data(), port, nullptr, 0);
        if (!sql) {
            ToLog<LogLevel::Error>(MakeLogMessage("MySQL Connect error"));
        }
        self.connect_queue_.push(sql);
    }
    self.free_count_ = max_connect_count;
}

inline void SqlConnectPool::Destroy(this SqlConnectPool &self) {
    {
        std::scoped_lock lock{self.mutex_};
        while (!self.connect_queue_.empty()) {
            auto con = self.connect_queue_.front();
            self.connect_queue_.pop();
            mysql_close(con);
        }
    }
    mysql_library_end();
}

inline SqlConnectPool* SqlConnectPool::Instance() {
    static SqlConnectPool pool;
    return std::addressof(pool);
}

inline MYSQL* SqlConnectPool::GetConnect(this SqlConnectPool &self) {
    MYSQL* result = nullptr;

    std::unique_lock lock{self.mutex_};
    if (self.connect_queue_.empty()) {
        self.cond_.wait(lock);
    }
    if (!self.connect_queue_.empty()) {
        result = self.connect_queue_.front();
        self.connect_queue_.pop();
    }
    self.use_count_ += 1;
    self.free_count_ -= 1;

    return result;
}

inline void SqlConnectPool::ReleaseConnect(this SqlConnectPool &self, MYSQL *con) {
    {
        std::unique_lock lock{self.mutex_};
        self.connect_queue_.push(con);
        self.use_count_ -= 1;
        self.free_count_ += 1;
    }
    self.cond_.notify_one();
}

inline int SqlConnectPool::GetFreeConnectCount(this SqlConnectPool &self) {
    std::scoped_lock lock{self.mutex_};
    return self.connect_queue_.size();
}

}

