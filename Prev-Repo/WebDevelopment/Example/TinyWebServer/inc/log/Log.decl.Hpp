#pragma once

#include "log/BlockQueue.hpp"
#include "buffer/Buffer.hpp"

#include <cstddef>
#include <cstdio>
#include <format>
#include <memory>
#include <source_location>
#include <string_view>
#include <thread>

namespace Koro {


template <typename T>
consteval auto GetTemplateNameWithFunction() noexcept {
    return std::string_view( std::source_location::current().function_name() );
}

template <auto Value>
consteval auto GetTemplateNameWithFunction() noexcept {
    return std::string_view(std::source_location::current().function_name());
}

consteval auto GetSplitPos() noexcept {
    constexpr auto result = GetTemplateNameWithFunction<nullptr>();
    constexpr auto left_size = result.find("nullptr");
    constexpr auto right_size = result.size() - left_size - 7;
    return std::pair{ left_size, right_size };
}

template <typename T>
consteval auto GetTemplateName() noexcept {
    auto [l, r] = GetSplitPos();
    constexpr auto result = GetTemplateNameWithFunction<T>();
    return result.substr(l, result.size() - l - r);
}

template <auto Value>
consteval auto GetTemplateName() noexcept {
    auto [l, r] = GetSplitPos();
    constexpr auto result = GetTemplateNameWithFunction<Value>();
    return result.substr(l, result.size() - l - r);
}

enum class LogLevel {
    Debug = 0,
    Info  = 1,
    Warn  = 2,
    Error = 3,
};

class Log {
private:
    static constexpr std::size_t LogPathLength = 256;
    static constexpr std::size_t LogNameLength = 256;
    static constexpr std::size_t LogMaxLimits  = 50000;

    std::string_view path_;
    std::string_view suffix_;

    int  max_lines_;
    int  line_count_;
    
    int  today_;
    
    LogLevel level_;
    bool is_async_;
    bool is_terminal_;
    
    Koro::Buffer buffer_;
    
    FILE *fp_;
    std::unique_ptr<Koro::BlockQueue<std::string>> blocK_queue_;
    std::unique_ptr<std::jthread> write_thread_;
    std::mutex mutex_;

private:
    Log();
    ~Log();

    // void AppendLogLevelTitle(this Log &self, int level);
    void WriteAsync(this Log &self);

public:
    void Init(this Log &self, Koro::LogLevel level, const char* path = "./log", const char* suffix =".log", int max_queue_capacity = 1024);

    static Log* Instance();
    static void FlushLogThread();

    void Write(this Log &self, std::string message);
    void Flush(this Log &self);

    LogLevel  GetLevel(this Log &self);
    void SetLevel(this Log &self, LogLevel level);
    bool IsOpen(this const Log &self) noexcept;
};

template <LogLevel Level>
void ToLog(std::string_view message);

// Use: MakeLogMessage(std::format("{}", 1)); 
std::string MakeLogMessage(std::string_view message, std::source_location current = std::source_location::current());

} // namespace Koro

// template <>
// class std::formatter<Koro::LogLevel> {
// public:

// };
