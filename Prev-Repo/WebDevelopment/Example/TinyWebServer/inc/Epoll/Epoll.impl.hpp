#pragma once

#include "Epoll.decl.hpp"
#include <cassert>
#include <sys/epoll.h>
#include <unistd.h>

namespace Koro {

inline Epoll::Epoll(std::size_t max_events) 
    :   epoll_fd_(epoll_create1(0)),
        events_(max_events) {
    assert(epoll_fd_ >= 0 && events_.size() > 0);
}

inline Epoll::~Epoll() {
    close(epoll_fd_);
}

inline bool Epoll::AddFd(this Epoll &self, int fd, std::uint32_t events) {
    if (fd < 0) {
        return false;
    }

    struct epoll_event event = {};
    event.data.fd = fd;
    event.events = events;
    return epoll_ctl(self.epoll_fd_, EPOLL_CTL_ADD, fd, &event) == 0;    
}

inline bool Epoll::ModFd(this Epoll &self, int fd, std::uint32_t events) {
    if (fd < 0)
        return false;
    struct epoll_event ev = {};
    ev.data.fd = fd;
    ev.events = events;
    return epoll_ctl(self.epoll_fd_, EPOLL_CTL_MOD, fd, &ev) == 0;
}

inline bool Epoll::DelFd(this Epoll &self, int fd) {
    if (fd < 0) return false;
    epoll_event ev = {};
    ev.data.fd = fd;
    return epoll_ctl(self.epoll_fd_, EPOLL_CTL_DEL, fd, &ev) == 0;
}

inline int Epoll::Wait(this Epoll &self, int timeouts_ms) {
    return epoll_wait(self.epoll_fd_, self.events_.data(), (int)self.events_.size(), timeouts_ms);
}

inline int Epoll::GetEventFd(this const Epoll &self, std::size_t i) {
    assert(i < self.events_.size() && i >= 0);
    return self.events_[i].data.fd;
}

inline std::uint32_t Epoll::GetEvents(this const Epoll &self, size_t i) {
    assert(i < self.events_.size() && i >= 0);
    return self.events_[i].events;
}

} // namespace Koro
