#pragma once

#include <atomic>
#include <cstddef>
#include <string>
#include <vector>

namespace Koro {

class Buffer {
private:
    std::vector<char> buffer_;
    std::atomic_size_t read_pos_;
    std::atomic_size_t write_pos_;
    
public:
    explicit Buffer(std::size_t init_buffer_size = 1024);
    ~Buffer() = default;

    std::size_t ReadAbleBytes(this const Buffer &self);
    std::size_t WriteAbleBytes(this const Buffer &self);
    std::size_t PrependAbleBytes(this const Buffer &self);

    const char* Peek(this const Buffer &self);
    void EnsureWriteAble(this Buffer &self, std::size_t length);
    void HasWritten(this Buffer &self, std::size_t length);

    void Retrieve(this Buffer &self, std::size_t length);
    void RetrieveUntil(this Buffer &self, const char* end);

    void RetrieveAll(this Buffer &self);
    std::string RetrieveAllToString(this Buffer &self);

    const char* BeginWriteConst(this const Buffer &self);
    char* BeginWrite(this Buffer &self);

    void Append(this Buffer &self, const std::string& str);
    void Append(this Buffer &self, const char* data, std::size_t length);
    void Append(this Buffer &self, const void* data, std::size_t length);
    void Append(this Buffer &self, const Buffer& other);

    ssize_t ReadFd(this Buffer &self, int fd, int* Errno);
    ssize_t WriteFd(this Buffer &self, int fd, int* Errno);

private:
    char* BeginPtr(this Buffer &self);
    const char* BeginPtr(this const Buffer &self);
    void MakeSpace(this Buffer &self, std::size_t length);
};

} // namespace Koro
