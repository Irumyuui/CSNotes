#pragma once

#include "buffer/Buffer.hpp"
#include <string>
#include <unordered_map>
#include "sys/stat.h"

namespace Koro {
    
class HttpResponse {
private:
    int code_;
    bool is_keep_alive_;

    std::string path_;
    std::string src_dir_;

    char* file_;
    struct stat file_stat_;

private:
    static const std::unordered_map<std::string, std::string> SuffixType;
    static const std::unordered_map<int, std::string>         CodeStatus;
    static const std::unordered_map<int, std::string>         CodePath;

public:
    HttpResponse();
    ~HttpResponse();

    void        Init(this HttpResponse &self, const std::string& src_dir, std::string& path, bool is_keep_alive = false, int code = -1);
    void        MakeResponse(this HttpResponse &self, Buffer& buffer);
    char*       GetFile(this HttpResponse &self);
    std::size_t GetFileLength(this const HttpResponse &self);
    void        ErrorContent(this const HttpResponse &self, Buffer& buffer, std::string message);
    int         GetCode(this const HttpResponse &self);
    void        UnmapFile(this HttpResponse &self);

private:
    void AddState(this HttpResponse &self, Buffer &buffer);
    void AddHeader(this HttpResponse &self, Buffer &buffer);
    void AddContent(this HttpResponse &self, Buffer &buffer);

    void        ErrorHtml(this HttpResponse &self);
    std::string GetFileType(this HttpResponse &self);
};

}
