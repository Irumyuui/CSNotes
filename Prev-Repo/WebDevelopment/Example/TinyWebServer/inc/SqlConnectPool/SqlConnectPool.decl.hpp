#pragma once

#include "mysql/mysql.h"
#include <condition_variable>
#include <mutex>
#include <queue>

namespace Koro {

class SqlConnectPool {
private:
    int use_count_;
    int free_count_;

    std::queue<MYSQL*> connect_queue_;
    std::mutex mutex_;
    std::condition_variable cond_;

private:
    SqlConnectPool();
    ~SqlConnectPool();

public:
    void Init(this SqlConnectPool &self,
              std::string_view host, int port,
              std::string_view user, std::string_view pwd,
              std::string_view dbName, int maxConnCnt);
    
    void Destroy(this SqlConnectPool &self);

    static SqlConnectPool* Instance();

    MYSQL* GetConnect(this SqlConnectPool &self);
    void ReleaseConnect(this SqlConnectPool &self, MYSQL *conn);
    int GetFreeConnectCount(this SqlConnectPool &self);
};

}
