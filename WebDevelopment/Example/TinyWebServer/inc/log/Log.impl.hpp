#pragma once

#include "Log.decl.Hpp"
#include "log/BlockQueue.decl.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdio>
#include <ctime>
#include <format>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <sys/stat.h>

namespace Koro {

inline Log::Log()
    : line_count_(0),
      today_(0),
      is_async_(false),
      fp_(nullptr),
      blocK_queue_(nullptr),
      write_thread_(nullptr) {
}

inline Log::~Log() {
    if (write_thread_ && write_thread_->joinable()) {
        // write_thread_->joinable();
        while (!blocK_queue_->Empty()) {
            blocK_queue_->Flush();
        }
        blocK_queue_->Close();
        write_thread_->join();
    }
    if (fp_) {
        std::scoped_lock lock{mutex_};
        Flush();
        fclose(fp_);
    }
}

inline void Log::WriteAsync(this Log &self) {
    std::string str = "";
    while (self.blocK_queue_->TryPop(str)) {
        std::scoped_lock lock{self.mutex_};
        fputs(str.c_str(), self.fp_);
    }
}

inline void Log::Init(this Log &self, Koro::LogLevel level, const char* path, const char* suffix, int max_queue_capacity) {
    self.is_terminal_ = false;
    self.level_ = level;

    if (max_queue_capacity > 0) {
        self.is_async_ = true;
        if (!self.blocK_queue_) {
            self.blocK_queue_  = std::make_unique<BlockQueue<std::string>>();
            self.write_thread_ = std::make_unique<std::jthread>();
        }
    } else {
        self.is_async_ = false;
    }

    self.line_count_ = 0;

    auto timer = time(nullptr);
    auto sys_time = localtime(&timer);
    auto t = *sys_time;
    self.path_ = path;
    self.suffix_ = suffix;

    std::array<char, Log::LogNameLength> filename{};
    snprintf(filename.data(), filename.size() - 1, "%s/%04d_%02d_%02d%s", 
        self.path_.data(), t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, self.suffix_.data());
    self.today_ = t.tm_mday;

    {
        std::scoped_lock lock{self.mutex_};
        self.buffer_.RetrieveAll();
        if (self.fp_) {
            self.Flush();
            fclose(self.fp_);
            self.fp_ = nullptr;
        }

        self.fp_ = fopen(filename.begin(), "a");
        if (self.fp_ == nullptr) {
            mkdir(self.path_.data(), 0777);
            self.fp_ = fopen(filename.data(), "a");
        }
        assert(self.fp_);
    }
}

inline Log* Log::Instance() {
    static Log log{};
    return std::addressof(log);
}

inline void Log::FlushLogThread() {
    Log::Instance()->WriteAsync();
}

inline void Log::Write(this Log &self, std::string message) {
    struct timeval now = {0, 0};
    gettimeofday(&now, nullptr);
    time_t tSec = now.tv_sec;
    struct tm *sysTime = localtime(&tSec);
    struct tm t = *sysTime;
    // va_list vaList;


    if (self.today_ != t.tm_mday || (self.line_count_ && (self.line_count_ % self.max_lines_) == 0)) {
        std::array<char, Log::LogNameLength> new_file{};
        std::array<char, 36> tail{};
        snprintf(tail.data(), 36, "%04d_%02d_%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);

        if (self.today_ != t.tm_mday)
        {
            snprintf(new_file.data(), new_file.size() - 72, "%s/%s%s", self.path_.data(), tail.data(), self.suffix_.data());
            self.today_ = t.tm_mday;
            self.line_count_ = 0;
        }
        else {
            snprintf(new_file.data(), new_file.size() - 72, "%s/%s-%d%s", self.path_.data(), tail.data(), (self.line_count_ / self.max_lines_), self.suffix_.data());
        }
        
        std::unique_lock lock{self.mutex_};
        
        lock.lock();
        self.Flush();

        fclose(self.fp_);
        self.fp_ = fopen(new_file.data(), "a");
        assert(self.fp_);
    }

    {
        std::unique_lock lock{self.mutex_};

        self.line_count_ += 1;
        int n = snprintf(self.buffer_.BeginWrite(), 128, "%d-%02d-%02d %02d:%02d:%02d.%06ld ",
                    t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
                    t.tm_hour, t.tm_min, t.tm_sec, now.tv_usec);
                    
        self.buffer_.HasWritten(n);
        // appendLogLevelTitle(level);

        // self.buffer_.HasWritten(std::string);
        self.buffer_.Append(message.data(), std::min(message.length(), self.buffer_.WriteAbleBytes()));
        self.buffer_.HasWritten(message.length());
        self.buffer_.Append("\n\0", 2);

        if(self.is_async_ && self.blocK_queue_ && !self.blocK_queue_->Full()) {
            self.blocK_queue_->Push(self.buffer_.RetrieveAllToString());
        } else {
            fputs(self.buffer_.Peek(), self.fp_);
        }
        self.buffer_.RetrieveAll();
    }
}

inline void Log::Flush(this Log &self) {
    if (self.is_async_) {
        self.blocK_queue_->Flush();
    }
    fflush(self.fp_);
}

inline LogLevel Log::GetLevel(this Log &self) {
    std::scoped_lock lock{self.mutex_};
    return self.level_;
}

inline void Log::SetLevel(this Log &self, LogLevel level) {
    std::scoped_lock lock{self.mutex_};
    self.level_ = level;
}

inline bool Log::IsOpen(this const Log &self) noexcept {
    return !self.is_terminal_;
}


template <LogLevel Level>
inline void ToLog(std::string_view message) {
    auto log = Log::Instance();
    if (log->IsOpen() && log->GetLevel() <= Level) {
        log->Write(std::format("[{}] {}", GetTemplateName<Level>(), message));
        log->Flush();
    }
}

// Use: MakeLogMessage(std::format("{}", 1)); 
inline std::string MakeLogMessage(std::string_view message, std::source_location current) {
    return std::format("{}[{}:{}]: {} => {}", current.file_name(), current.line(), current.column(), current.function_name(), message);
}

} // namespace Koro
