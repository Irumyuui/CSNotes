#pragma once

#include <format>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "buffer/Buffer.hpp"
#include "log/Log.hpp"

namespace Koro {

enum class HttpCode {
    NoRequest,
    GetRequest,
    BadRequest,
    NoResourse,
    ForbiddenRequest,
    FileRequest,
    InternalError,
    ClosedConnection,
};

enum class ParseState {
    RequestLine,
    Headers,
    Body,
    Finish,
};

class HttpRequest {
private:
    ParseState state_;
    
    std::string method_;
    std::string path_;
    std::string version_;
    std::string body_;
    bool linger_;
    size_t content_length_;

    std::unordered_map<std::string, std::string> header_;
    std::unordered_map<std::string, std::string> post_;

    static const std::unordered_set<std::string> DefaultHtml;
    static const std::unordered_map<std::string, int> DefaultHtmlTag;


public:
    HttpRequest() {
        Init();
    }
    
    ~HttpRequest() = default;
    
    void Init(this HttpRequest &self);
    
    HttpCode Parse(this HttpRequest &self, Koro::Buffer &buffer);

    // std::string getPathConst(this const HttpRequest &self) {
    //     return self.path_;
    // }
    
    const std::string& GetPath(this const HttpRequest &self) {
        return self.path_;
    }

    std::string& GetPath(this HttpRequest &self) {
        return self.path_;
    }


    const std::string& GetMethod(this const HttpRequest &self) {
        return self.method_;
    }
    
    const std::string& GetVersion(this const HttpRequest &self) {
        return self.version_;
    }
    
    bool IsKeepAlive(this const HttpRequest &self) {
        if (self.header_.contains("Connection")) {
            return self.linger_;
        }
        return false;
    }

private:
    HttpCode ParseRequestLine(this HttpRequest &self, const std::string& line);
    HttpCode ParseHeader(this HttpRequest &self, const std::string& line);
    HttpCode ParseBody(this HttpRequest &self);

    void ParsePath(this HttpRequest &self);
    void ParseFromUrlEncoded(this HttpRequest &self);

    static bool UserVerify(const std::string& name, const std::string& pwd, bool is_login);

    static int ConvertToHex(char ch) {
        if (ch >= 'A' && ch <= 'F') {
            return ch - 'A' + 10;
        } else if (ch >= 'a' && ch <= 'f') {
            return ch - 'a' + 10;
        } else {
            ToLog<LogLevel::Debug>(MakeLogMessage(std::format("Try to hex: {}", ch)));
            return ch;
        }
    }
};


}
