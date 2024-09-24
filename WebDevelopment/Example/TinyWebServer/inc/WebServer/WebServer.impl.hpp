#pragma once

#include "Epoll/Epoll.decl.hpp"
#include "Http/HttpConnect/HttpConnect.decl.hpp"
#include "SqlConnectPool/SqlConnectPool.decl.hpp"
#include "Timer/Timer.hpp"
#include "WebServer/WebServer.decl.hpp"
#include <asm-generic/socket.h>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <format>
#include <memory>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include "ThreadPool/ThreadPool.hpp"
#include "SqlConnectPool/SqlConnectPool.hpp"
#include "log/Log.decl.Hpp"

namespace Koro {

inline WebServer::WebServer(int port, int trig_mode, int timeout_ms, bool open_linger,
        int sql_port, const char* sql_user, const char* sql_password,
        const char* db_name, int connect_pool_count,
        [[maybe_unused]] int thread_count, [[maybe_unused]] int max_requests,
        bool open_log, int log_level, int log_que_size) 
        
    : port_(port), open_linger_(open_linger), timeout_ms_(timeout_ms), is_shutdown_(false),
    timer_(std::make_unique<TimeScheduler>()), epoll_(std::make_unique<Epoll>())  
{
    src_dir_ = getcwd(nullptr, 256);
    assert(src_dir_);
    strncat(src_dir_, "/src/", 16);

    HttpConnect::user_count_ = 0;
    HttpConnect::src_dir_ = src_dir_;

    [[maybe_unused]] auto thread_pool = ThreadPool::Instance();
    SqlConnectPool::Instance()->Init("localhost", sql_port, sql_user, sql_password, db_name, connect_pool_count);
    InitEventMode(trig_mode);
    if (!InitSocket()) {
        is_shutdown_ = true;
        // return;
    }

    if (open_log) {
        Log::Instance()->Init(static_cast<LogLevel>(log_level), "./log", ".log", log_que_size);
    
        if (is_shutdown_) {
            ToLog<LogLevel::Error>(MakeLogMessage("Server init failed."));
        } else {
            ToLog<LogLevel::Info>(MakeLogMessage("Server init."));
            ToLog<LogLevel::Info>(MakeLogMessage(std::format("Port: {}, OpenLinger: {}", port_, open_linger_ ? "true" : "false")));
            ToLog<LogLevel::Info>(MakeLogMessage(std::format("ListenMode: {}, OpenConnectMode: {}",
                listen_event_opt_ & EPOLLET ? "ET" : "LT",
                connect_event_opt_ & EPOLLET ? "ET" : "LT"
            )));
            ToLog<LogLevel::Info>(MakeLogMessage(std::format("Log level: {}", log_level)));
            ToLog<LogLevel::Info>(MakeLogMessage(std::format("SrcDir: {}", HttpConnect::src_dir_)));
            ToLog<LogLevel::Info>(MakeLogMessage(std::format("SqlConnectPool count: {}", connect_pool_count)));
        }
    }
}

inline WebServer::~WebServer() {
    close(listen_fd_);
    is_shutdown_ = true;
    free(src_dir_);
    SqlConnectPool::Instance()->Destroy();
}

inline void WebServer::InitEventMode(this WebServer &self, int trig_mode) {
    self.listen_event_opt_ = EPOLLRDHUP;
    self.connect_event_opt_ = EPOLLONESHOT | EPOLLRDHUP;
    
    if (trig_mode == 0) {
        // nothing
    } else if (trig_mode == 1) {
        self.connect_event_opt_ |= EPOLLET;
    } else if (trig_mode == 2) {
        self.listen_event_opt_ |= EPOLLET;
    } else {
        self.connect_event_opt_ |= EPOLLET;
        self.listen_event_opt_ |= EPOLLET;
    }

    HttpConnect::is_ET_mode_ = (self.connect_event_opt_ & EPOLLET);
}

inline void WebServer::Start(this WebServer &self) {
    int time_ms = -1;
    if (!self.is_shutdown_) {
        ToLog<LogLevel::Info>(MakeLogMessage("Server start."));
    }

    while (!self.is_shutdown_) {
        if (self.timeout_ms_ > 0) {
            time_ms = self.timer_->GetNextTick();
        }

        auto event_wait_count = self.epoll_->Wait(time_ms);
        for (int i = 0; i < event_wait_count; i ++) {
            auto fd = self.epoll_->GetEventFd(i);
            auto events = self.epoll_->GetEvents(i);

            if (fd == self.listen_fd_) {
                self.DealListen();    
            } else if (events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                assert(self.users.contains(fd));
                self.CloseConnect(&self.users_[fd]);
            } else if (events & EPOLLIN) {
                assert(self.users.contains(fd));
                self.DealRead(&self.users_[fd]);
            } else if (event_wait_count & EPOLLOUT) {
                assert(self.users.contains(fd));
                self.DealWrite(&self.users_[fd]);
            } else {
                ToLog<LogLevel::Error>(MakeLogMessage("What the fuck of this event."));
            }
        }
    }
}

inline void WebServer::SendError([[maybe_unused]] this WebServer &self, int fd, const char *info) {
    assert(fd > 0);
    if (auto result = send(fd, info, strlen(info), 0); result < 0) {
        ToLog<LogLevel::Warn>(MakeLogMessage(std::format("Send error to client{} error.", fd)));
    }
    close(fd);
}

inline void WebServer::CloseConnect(this WebServer &self, HttpConnect* client) {
    assert(client);
    ToLog<LogLevel::Info>(MakeLogMessage(std::format("Client[{}] quit.", client->GetFd())));
    self.epoll_->DelFd(client->GetFd());
    client->CloseConnect();
}

inline void WebServer::AddClient(this WebServer &self, int fd, struct sockaddr_in addr) {
    assert(fd > 0);

    self.users_[fd].Init(fd, addr);

    if (self.timeout_ms_ > 0) {
        self.timer_->Push(fd, std::chrono::milliseconds(self.timeout_ms_), [&self, fd] {
            self.CloseConnect(&self.users_[fd]);
        });
    }
    self.epoll_->AddFd(fd, EPOLLIN | self.connect_event_opt_);

    self.SetFdNonblock(fd);
    ToLog<LogLevel::Info>(MakeLogMessage(std::format("Client[{}] in.", self.users_[fd].GetFd())));
}

inline void WebServer::DealListen(this WebServer &self) {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    do {
        int fd = accept(self.listen_fd_, (struct sockaddr*)&addr, &len);
        if (fd <= 0) return;
        if (HttpConnect::user_count_ >= MAX_FD) {
            self.SendError(fd, "Server busy.");
            // LOG_WARN("Clients is full!");
            ToLog<LogLevel::Warn>(MakeLogMessage("Clients is full."));
            return;
        }
        self.AddClient(fd, addr);
    } while (self.listen_event_opt_ & EPOLLET);
}

inline void WebServer::DealRead(this WebServer &self, HttpConnect *client) {
    assert(client);
    self.ExtentTime(client);
    ThreadPool::Instance()->Submit([&self, client] {
        self.OnRead(client);
    });
}

inline void WebServer::DealWrite(this WebServer &self, HttpConnect *client) {
    assert(client);
    self.ExtentTime(client);
    ThreadPool::Instance()->Submit([&self, client] {
        self.OnWrite(client);
    });
}

inline void WebServer::ExtentTime(this WebServer &self, HttpConnect *client) {
    assert(client);
    if (self.timeout_ms_ > 0) {
        self.timer_->AdjustDelay(client->GetFd(), std::chrono::milliseconds(self.timeout_ms_));
    }
}

inline void WebServer::OnRead(this WebServer &self, HttpConnect* client) {
    assert(client);
    int ret = -1;
    int readErrno = 0;
    ret = client->Read(&readErrno);
    if (ret <= 0 && readErrno != EAGAIN) {
        self.CloseConnect(client);
        return;
    }
    self.OnProcess(client);
}

inline void WebServer::OnProcess(this WebServer &self, HttpConnect* client) {
    if (client->Process()) {
        self.epoll_->ModFd(client->GetFd(), self.connect_event_opt_ | EPOLLOUT);
    } else {
        self.epoll_->ModFd(client->GetFd(), self.connect_event_opt_ | EPOLLIN);
    }
}

inline void WebServer::OnWrite(this WebServer &self, HttpConnect* client) {
    assert(client);
    int writeErrno = 0;
    auto result = client->Write(&writeErrno);
    if (client->ToWriteBytes() == 0) {
        if (client->IsKeepAlive()) {
            self.OnProcess(client);
            return;
        }
    } else if (result < 0) {
        if (writeErrno == EAGAIN) {
            self.epoll_->ModFd(client->GetFd(), self.connect_event_opt_ | EPOLLOUT);
            return;
        }
    }
    self.CloseConnect(client);
}

inline int WebServer::SetFdNonblock(int fd) {
    assert(fd > 0);
    return fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK);
}

inline bool WebServer::InitSocket(this WebServer &self) {
    if (self.port_ > 65536 || self.port_ < 1024) {
        ToLog<LogLevel::Error>(MakeLogMessage(std::format("Invalid port: {}", self.port_)));
        return false;
    }
    
    struct linger opt_linger{};
    if (self.open_linger_) {
        opt_linger.l_linger = 1;
        opt_linger.l_linger = 20;
    }

    self.listen_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (self.listen_fd_ < 0) {
        ToLog<LogLevel::Error>(MakeLogMessage(std::format("Create socket error, prot: {}", self.port_)));
        return false;
    }

    if (auto result = setsockopt(self.listen_fd_, SOL_SOCKET, SO_LINGER, &opt_linger, sizeof(opt_linger)); result == -1) {
        close(self.listen_fd_);
        ToLog<LogLevel::Error>(MakeLogMessage(std::format("Port: {} init linger, error", self.port_)));
        return false;
    }

    struct sockaddr_in addr;
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port        = htons(self.port_);

    if (auto result = bind(self.listen_fd_, (struct sockaddr*)(std::addressof(addr)), sizeof(addr)); result == -1) {
        ToLog<LogLevel::Error>(MakeLogMessage(std::format("Bind port: {} error", self.port_)));
        close(self.listen_fd_);
        return false;
    }

    if (auto result = listen(self.listen_fd_, 10); result == -1) {
        ToLog<LogLevel::Error>(MakeLogMessage(std::format("Listen port: {} error", self.port_)));
        close(self.listen_fd_);
        return false;
    }

    if (auto result = self.epoll_->AddFd(self.listen_fd_, self.listen_event_opt_ | EPOLLIN); result == 0) {
        ToLog<LogLevel::Error>(MakeLogMessage(std::format("Add lisent error, prot: {}", self.port_)));
        close(self.listen_fd_);
        return false;
    }

    self.SetFdNonblock(self.listen_fd_);
    ToLog<LogLevel::Info>(MakeLogMessage(std::format("Server port: {}", self.port_)));
    return true;
}

}
