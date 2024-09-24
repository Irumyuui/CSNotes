#pragma once

#include <cassert>
#include <format>
#include <string_view>
#include <sys/types.h>
#include <unistd.h>

#include "Http/HttpRequest/HttpRequest.decl.hpp"
#include "HttpConnect.decl.hpp"
#include "log/Log.decl.Hpp"
#include "log/Log.hpp"

namespace Koro {

inline std::string_view HttpConnect::src_dir_;

inline std::atomic_int HttpConnect::user_count_;

inline bool HttpConnect::is_ET_mode_;

inline HttpConnect::HttpConnect() : fd_(-1), addr_{}, is_terminal_(false) {
}

inline void HttpConnect::Init(this HttpConnect &self, int fd, const struct sockaddr_in &addr) {
    assert(fd > 0);

    user_count_ += 1;
    self.addr_ = addr;
    self.fd_ = fd;
    self.write_buffer_.RetrieveAll();
    self.read_buffer_.RetrieveAll();
    self.is_terminal_ = false;
    
    ToLog<LogLevel::Debug>(MakeLogMessage(std::format("Client: [{}]({}:{}) in, User count: {}", self.fd_, self.GetIP(), self.getPort(), static_cast<int>(self.user_count_))));

    self.request_.Init();
}

inline void HttpConnect::CloseConnect(this HttpConnect &self) {
    self.response_.UnmapFile();
    if (!self.is_terminal_) {
        self.is_terminal_ = true;
        self.user_count_ -= 1;
        close(self.fd_);
        ToLog<LogLevel::Debug>(MakeLogMessage(std::format("Client: [{}]({}:{}) in, User count: {}", self.fd_, self.GetIP(), self.getPort(), static_cast<int>(self.user_count_))));
    }
}

inline
ssize_t HttpConnect::Read(this HttpConnect &self, int *result) {
    ssize_t length = -1;
    do {
        length = self.read_buffer_.ReadFd(self.fd_, result);
        if (length <= 0) {
            *result = errno;
            break;
        }
    } while (self.is_ET_mode_);
    return length;
}

inline
ssize_t HttpConnect::Write(this HttpConnect &self, int* Errno) {
    ssize_t length = -1;
    
    do {
        length = writev(self.fd_, self.iov_.data(), self.iov_count_);
        if (length <= 0) {
            *Errno = errno;
            break;
        }

        if (self.iov_[0].iov_len + self.iov_[1].iov_len == 0) {
            break;
        } else if (static_cast<std::size_t>(length) > self.iov_[0].iov_len) {
            self.iov_[1].iov_base = static_cast<uint8_t*>(self.iov_[1].iov_base) + (length - self.iov_[0].iov_len);
            self.iov_[1].iov_len -= (length - self.iov_[0].iov_len);

            if (self.iov_[0].iov_len) {
                self.iov_[0].iov_len = 0;
                self.write_buffer_.RetrieveAll();
            }
        } else {
            self.iov_[0].iov_base = static_cast<uint8_t*>(self.iov_[0].iov_base) + length;
            self.iov_[0].iov_len -= length;
            self.write_buffer_.Retrieve(length);
        }
    } while (self.is_ET_mode_ || self.ToWriteBytes() > 10240);

    return length;
}

inline
bool HttpConnect::Process(this HttpConnect &self) {
    if (self.read_buffer_.ReadAbleBytes() <= 0) {
        return false;
    }

    if (auto ret = self.request_.Parse(self.read_buffer_); ret == HttpCode::NoRequest) {
        return false;
    } else if (ret == HttpCode::GetRequest) {
        ToLog<LogLevel::Debug>(MakeLogMessage(std::format("Path: {}", self.request_.GetPath())));

        self.response_.Init(std::string(self.src_dir_), self.request_.GetPath(), self.request_.IsKeepAlive(), 200);
        self.request_.Init();
    } else if (ret == HttpCode::BadRequest) {
        self.response_.Init(std::string(self.src_dir_), self.request_.GetPath(), false, 400);
    }

    self.response_.MakeResponse(self.write_buffer_);

    self.iov_[0].iov_base = (char*)self.write_buffer_.Peek();
    self.iov_[0].iov_len = self.write_buffer_.ReadAbleBytes();
    self.iov_count_ = 1;

    if (self.response_.GetFileLength() > 0 && self.response_.GetFile()) {
        self.iov_[1].iov_base = self.response_.GetFile();
        self.iov_[1].iov_len = self.response_.GetFileLength();
        self.iov_count_ = 2;
    }

    ToLog<LogLevel::Debug>(MakeLogMessage(std::format("FileSize: %d, IovCount: %d, Write: %d bytes", self.response_.GetFileLength(), self.iov_count_, self.ToWriteBytes())));

    return true;
}


}
