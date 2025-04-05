#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <sys/epoll.h>

namespace Koro {

class Epoll {
private:
    int epoll_fd_;
    std::vector<struct epoll_event> events_;

public:
    explicit Epoll(std::size_t max_events = 1024);
    ~Epoll();

    bool AddFd(this Epoll &self, int fd, std::uint32_t events);
    bool ModFd(this Epoll &self, int fd, std::uint32_t events);
    bool DelFd(this Epoll &self, int fd);

    int Wait(this Epoll &self, int timeouts_ms = -1);

    int GetEventFd(this const Epoll &self, std::size_t i);
    std::uint32_t GetEvents(this const Epoll &self, size_t i);
};

}
