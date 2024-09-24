#pragma once

#include "Buffer.decl.hpp"
#include <algorithm>
#include <array>
#include <bits/types/struct_iovec.h>
#include <cassert>
#include <cstddef>
#include <string>
#include <unistd.h>
#include <sys/uio.h>

namespace Koro {
    

inline Buffer::Buffer(std::size_t init_buffer_size)
    : buffer_(init_buffer_size), read_pos_(0), write_pos_(0) {}

inline std::size_t Buffer::ReadAbleBytes(this const Buffer &self) {
    return self.write_pos_ - self.read_pos_;
}

inline std::size_t Buffer::WriteAbleBytes(this const Buffer &self) {
    return self.buffer_.size() - self.write_pos_;
}

inline std::size_t Buffer::PrependAbleBytes(this const Buffer &self) {
    return self.read_pos_;
}

inline const char* Buffer::Peek(this const Buffer &self) {
    return self.BeginPtr() + self.read_pos_;
}

inline void Buffer::Retrieve(this Buffer &self, std::size_t length) {
    assert(length <= self.ReadAbleBytes() && "");
    self.read_pos_ += length;
}

inline void Buffer::RetrieveUntil(this Buffer &self, const char *end) {
    assert(self.Peek() <= end && "");
    self.Retrieve(end - self.Peek());
}

inline void Buffer::RetrieveAll(this Buffer &self) {
    std::ranges::fill(self.buffer_, char{});
    self.read_pos_ = 0;
    self.write_pos_ = 0;
}

inline std::string Buffer::RetrieveAllToString(this Buffer &self) {
    std::string result(self.Peek(), self.ReadAbleBytes());
    self.RetrieveAll();
    return result;
}

inline const char* Buffer::BeginWriteConst(this const Buffer &self) {
    return self.BeginPtr() + self.write_pos_;
}

inline char* Buffer::BeginWrite(this Buffer &self) {
    return self.BeginPtr() + self.write_pos_;
}

inline void Buffer::HasWritten(this Buffer &self, std::size_t length) {
    self.write_pos_ += length;
}

inline void Buffer::Append(this Buffer &self, const void *data, std::size_t length) {
    self.Append(static_cast<const char*>(data), length);
}

inline void Buffer::Append(this Buffer &self, const char *data, std::size_t length) {
    self.EnsureWriteAble(length);
    std::copy(data, data + length, self.BeginWrite());
    self.HasWritten(length);
}

inline void Buffer::Append(this Buffer &self, const std::string &str) {
    self.Append(str.data(), str.length());
}

inline void Buffer::Append(this Buffer &self, const Buffer &other) {
    self.Append(other.Peek(), other.ReadAbleBytes());
}

inline void Buffer::EnsureWriteAble(this Buffer &self, std::size_t length) {
    if (self.WriteAbleBytes() < length) {
        self.MakeSpace(length);
    }
}

inline ssize_t Buffer::ReadFd(this Buffer &self, int fd, int* Errno) {
    std::array<char, 65536> buffer;
    std::array<struct iovec, 2> iov;

    const auto WriteAbleBytes = self.WriteAbleBytes();
    
    iov[0].iov_base = self.BeginPtr() + self.write_pos_;
    iov[0].iov_len = WriteAbleBytes;
    iov[1].iov_base = buffer.data();
    iov[1].iov_len = buffer.size();

    const auto length = readv(fd, iov.data(), 2);
    if (length < 0) {
        *Errno = errno;
    } else if (static_cast<std::size_t>(length) <= WriteAbleBytes) {
        self.write_pos_ += length;
    } else {
        self.write_pos_ = self.buffer_.size();
        self.Append(buffer.data(), length - WriteAbleBytes);
    }
    
    return length;
}

inline ssize_t Buffer::WriteFd(this Buffer &self, int fd, int* Errno) {
    auto read_size = self.ReadAbleBytes();
    auto length = write(fd, self.Peek(), read_size);

    if (length < 0) {
        *Errno = errno;
    } else {
        self.read_pos_ += length;
    }

    return length;
}

inline char* Buffer::BeginPtr(this Buffer &self) {
    return self.buffer_.data();
}

inline const char* Buffer::BeginPtr(this const Buffer &self) {
    return self.buffer_.data();
}

inline void Buffer::MakeSpace(this Buffer &self, std::size_t length) {
    if (self.WriteAbleBytes() + self.PrependAbleBytes() < length) {
        self.buffer_.resize(self.write_pos_ + length + 1);
    } else {
        auto read_able_size = self.ReadAbleBytes();
        std::copy(self.BeginPtr() + self.read_pos_, self.BeginPtr() + self.write_pos_, self.BeginPtr());
        self.read_pos_ = 0;
        self.write_pos_ = read_able_size;
    }
}

} // namespace Koro
