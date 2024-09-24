#pragma once

#include "HttpResponse.decl.hpp"
#include "log/Log.decl.Hpp"
#include <cassert>
#include <cstdint>
#include <fcntl.h>
#include <format>
#include <sys/mman.h>
#include <sys/stat.h>

namespace Koro {

inline const std::unordered_map<std::string, std::string> HttpResponse::SuffixType =
{
    { ".html",  "text/html" },
    { ".xml",   "text/xml" },
    { ".xhtml", "application/xhtml+xml" },
    { ".txt",   "text/plain" },
    { ".rtf",   "application/rtf" },
    { ".pdf",   "application/pdf" },
    { ".word",  "application/msword" },
    { ".png",   "image/png" },
    { ".gif",   "image/gif" },
    { ".jpg",   "image/jpeg" },
    { ".jpeg",  "image/jpeg" },
    { ".au",    "audio/basic" },
    { ".mpeg",  "video/mpeg" },
    { ".mpg",   "video/mpeg" },
    { ".avi",   "video/x-msvideo" },
    { ".gz",    "application/x-gzip" },
    { ".tar",   "application/x-tar" },
    { ".css",   "text/css "},
    { ".js",    "text/javascript "},
};

inline const std::unordered_map<int, std::string> HttpResponse::CodeStatus = 
{
    { 200, "OK" },
    { 400, "Bad Request" },
    { 403, "Forbidden" },
    { 404, "Not Found" },
};

inline const std::unordered_map<int, std::string> CodePath = 
{
    { 400, "/400.html" },
    { 403, "/403.html" },
    { 404, "/404.html" },
};

inline HttpResponse::HttpResponse()
    : code_(-1),
      is_keep_alive_(false),
      path_(""),
      src_dir_(""),
      file_(nullptr),
      file_stat_{}
{
}

inline HttpResponse::~HttpResponse() {
    UnmapFile();
}

inline void HttpResponse::Init(this HttpResponse &self, const std::string& src_dir, std::string& path, bool is_keep_alive, int code) {
    assert(src_dir != "");
    if (self.file_) {
        self.UnmapFile();
    }
    self.code_ = code;
    self.is_keep_alive_ = is_keep_alive;
    self.path_ = path;
    self.src_dir_ = src_dir;
    self.file_ = nullptr;
    self.file_stat_ = {};
}

inline void HttpResponse::MakeResponse(this HttpResponse &self, Buffer& buffer) {
    if (stat((self.src_dir_ + self.path_).data(), &self.file_stat_) < 0 || S_ISDIR(self.file_stat_.st_mode)) {
        self.code_ = 404;
    } else if (!(self.file_stat_.st_mode & S_IROTH)) {
        self.code_ = 403;
    }
    else if (self.code_ == -1)
    {
        self.code_ = 200;
    }
    self.ErrorHtml();
    self.AddState(buffer);
    self.AddHeader(buffer);
    self.AddContent(buffer);
}

inline char* HttpResponse::GetFile(this HttpResponse &self) {
    return self.file_;
}

inline std::size_t HttpResponse::GetFileLength(this const HttpResponse &self) {
    return self.file_stat_.st_size;
}

inline void HttpResponse::ErrorContent(this const HttpResponse &self, Buffer& buffer, std::string message) {
    std::string body = "<html><title>Error</title><body bgcolor=\"ffffff\">";
    std::string status;
        
    if (CodeStatus.contains(self.code_)) {
        status = CodeStatus.find(self.code_)->second;
    } else {
        status = "Bad Request";
    }

    body += std::to_string(self.code_) + " : " + status + "\n";
    body += "<p>" + message + "</p>";
    body += "<hr><em>SimpleWebServer</em></body></html>";

    buffer.Append(std::format("Content-length: {}\r\n\r\n", body.size()));
    buffer.Append(body);
}

inline int HttpResponse::GetCode(this const HttpResponse &self) {
    return self.code_;
}

inline void HttpResponse::UnmapFile(this HttpResponse &self) {
    if (self.file_) {
        munmap(self.file_, self.file_stat_.st_size);
        self.file_ = nullptr;
        self.file_stat_ = {};
    }
}

inline void HttpResponse::AddState(this HttpResponse &self, Buffer &buffer) {
    std::string status;
    if (CodeStatus.contains(self.code_)) {
        status = CodeStatus.find(self.code_)->second;
    } else {
        self.code_ = 400;
        status = CodeStatus.find(400)->second;
    }
    buffer.Append(std::format("HTTP/1.1 {} {}\r\n", self.code_, status));
}

inline void HttpResponse::AddHeader(this HttpResponse &self, Buffer &buffer) {
    buffer.Append("Connection: ");
    if (self.is_keep_alive_) {
        buffer.Append("keep-alive\r\n");
        buffer.Append("keep-alive: max=6, timeout=120\r\n");
    } else {
        buffer.Append("close\r\n");
    }
    buffer.Append(std::format("Content-type: {}\r\n", self.GetFileType()));
}

inline void HttpResponse::AddContent(this HttpResponse &self, Buffer &buffer) {
    int src_fd = open((self.src_dir_ + self.path_).data(), O_RDONLY);
    if (src_fd < 0) {
        self.ErrorContent(buffer, "File Not Found!");
        return;
    }

    ToLog<LogLevel::Debug>(MakeLogMessage(std::format("File path: {}{}", self.src_dir_, self.path_)));

    int *mmap_result = (int*)mmap(0, self.file_stat_.st_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
    if (*mmap_result == -1) {
        self.ErrorContent(buffer, "File Not Found!");
        return;
    }
    self.file_ = (char*)mmap_result;
    close(src_fd);
    buffer.Append(std::format("Content-length: {}\r\n\r\n", static_cast<std::int64_t>(self.file_stat_.st_size)));
}

inline void HttpResponse::ErrorHtml(this HttpResponse &self) {
    if (CodePath.contains(self.code_)) {
        self.path_ = CodePath.find(self.code_)->second;
        stat((self.src_dir_ + self.path_).data(), &self.file_stat_);
    }
}

inline std::string HttpResponse::GetFileType(this HttpResponse &self) {
    auto idx = self.path_.find_last_of('.');
    if (idx == std::string::npos)
        return "text/plain";

    auto suffix = self.path_.substr(idx);
    if (SuffixType.contains(suffix)) {
        return SuffixType.find(suffix)->second;
    }
    return "text/plain";
}

}
