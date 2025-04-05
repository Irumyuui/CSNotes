#pragma once

#include <fcntl.h>
#include <memory>
#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unordered_map>

#include "Http/HttpConnect/HttpConnect.hpp"
#include "Timer/Timer.hpp"
#include "Epoll/Epoll.hpp"

namespace Koro {

class WebServer {
private:
    int   port_;
    bool  open_linger_;
    int   timeout_ms_;
    bool  is_shutdown_;
    int   listen_fd_;
    char* src_dir_;

    uint32_t listen_event_opt_;
    uint32_t connect_event_opt_;

    std::unique_ptr<TimeScheduler> timer_;
    std::unique_ptr<Epoll> epoll_;
    std::unordered_map<int, HttpConnect> users_;

    static const int MAX_FD = 65536;

public:
    WebServer(
        int port, int trig_mode, int timeout_ms, bool open_linger,
        int sql_port, const char* sql_user, const char* sql_password,
        const char* db_name, int connect_pool_count,
        int thread_count, int max_requests,
        bool open_log, int log_level, int log_que_size);
    
    ~WebServer();

    void Start(this WebServer &self);

private:
    bool InitSocket(this WebServer &self);
    void InitEventMode(this WebServer &self, int trig_mode);
    void AddClient(this WebServer &self, int fd, sockaddr_in addr);

    void DealListen(this WebServer &self);
    void DealWrite(this WebServer &self, HttpConnect* client);
    void DealRead(this WebServer &self, HttpConnect* client);

    void SendError(this WebServer &self, int fd, const char* info);
    void ExtentTime(this WebServer &self, HttpConnect* client);
    void CloseConnect(this WebServer &self, HttpConnect* client);

    void OnRead(this WebServer &self, HttpConnect* client);
    void OnWrite(this WebServer &self, HttpConnect* client);
    void OnProcess(this WebServer &self, HttpConnect* client);

    static int SetFdNonblock(int fd);
};

}
