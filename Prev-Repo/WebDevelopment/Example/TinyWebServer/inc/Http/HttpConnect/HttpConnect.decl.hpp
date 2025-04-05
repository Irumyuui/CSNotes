#pragma once

#include <array>
#include <bits/types/struct_iovec.h>
#include <string_view>
#include <sys/types.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <errno.h>

#include "buffer/Buffer.hpp"
#include "Http/HttpRequest/HttpRequest.hpp"
#include "Http/HttpResponse/HttpResponse.hpp"

namespace Koro {

class HttpConnect {
private:
    int                         fd_;
    struct sockaddr_in          addr_;
    bool                        is_terminal_;
    int                         iov_count_;
    std::array<struct iovec, 2> iov_{};
    Buffer                      read_buffer_;
    Buffer                      write_buffer_;
    HttpRequest                 request_;
    HttpResponse                response_;

public:
    HttpConnect();

    ~HttpConnect() {
        CloseConnect();
    }

    void Init(this HttpConnect &self, int socket_fd, const struct sockaddr_in& addr);
    
    ssize_t Read(this HttpConnect &self, int* Errno);
    
    ssize_t Write(this HttpConnect &self, int* Errno);

    void CloseConnect(this HttpConnect &self);

    int GetFd(this const HttpConnect &self) noexcept {
        return self.fd_;
    }

    struct sockaddr_in GetAddr(this const HttpConnect &self) noexcept {
        return self.addr_;
    }
    
    int getPort(this const HttpConnect &self) noexcept {
        return self.addr_.sin_port;
    }

    const char* GetIP(this const HttpConnect &self) {
        return inet_ntoa(self.addr_.sin_addr);
    }

    bool Process(this HttpConnect &self);

    int ToWriteBytes(this HttpConnect &self)
    {
        return self.iov_[0].iov_len + self.iov_[1].iov_len;
    }

    bool IsKeepAlive(this const HttpConnect &self)
    {
        return self.request_.IsKeepAlive();
    }

    static bool is_ET_mode_;
    static std::string_view src_dir_;
    static std::atomic_int user_count_;
};



}
