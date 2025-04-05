#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdio>
#include <format>
#include <regex>
#include <string_view>
#include "mysql/mysql.h"

#include "HttpRequest.decl.hpp"
#include "log/Log.hpp"
#include "buffer/Buffer.hpp"
#include "SqlConnectPool/SqlConnet.hpp"
#include "SqlConnectPool/SqlConnectPool.hpp"

namespace Koro {

const char CRLF[] = "\r\n";

inline
const std::unordered_set<std::string> HttpRequest::DefaultHtml
{
    "/index", "/register", "/login",
    "/welcome", "/video", "/picture",
};

inline
const std::unordered_map<std::string, int> DefaultHtmlTag
{
    {"/register.html", 0},
    {"/login.html", 1}
};

inline void HttpRequest::Init(this HttpRequest &self) {
    self.method_ = "";
    self.path_ = "";
    self.version_ = "";
    self.body_ = "";
    self.linger_ = false;
    self.state_ = ParseState::RequestLine;
    self.header_.clear();
    self.post_.clear();
}

inline 
HttpCode HttpRequest::Parse(this HttpRequest &self, Buffer &buffer) {
    while (buffer.ReadAbleBytes()) {
        const char *line_end = nullptr;
        std::string line;

        if (self.state_ != ParseState::Body) {
            line_end = std::search(buffer.Peek(), buffer.BeginWriteConst(), CRLF, CRLF + 2);
            if (line_end == buffer.BeginWriteConst()) {
                return HttpCode::NoRequest;
            }
            line = std::string(buffer.Peek(), line_end);
            buffer.RetrieveUntil(line_end + 2);
        } else {
            self.body_ += buffer.RetrieveAllToString();
            if (self.body_.size() < self.content_length_) {
                return HttpCode::NoRequest;
            }
        }

        if (self.state_ == ParseState::RequestLine) {
            if (auto result = self.ParseRequestLine(line); result == HttpCode::BadRequest) {
                return HttpCode::BadRequest;
            }
            self.ParsePath();
        } else if (self.state_ == ParseState::Headers) {
            if (auto result = self.ParseHeader(line); result == HttpCode::GetRequest) {
                return HttpCode::GetRequest;
            }            
        } else if (self.state_ == ParseState::Body) {
            if (auto result = self.ParseBody(); result == HttpCode::GetRequest) {
                return HttpCode::GetRequest;
            }
        } else {
            // what.
        }
    }

    ToLog<LogLevel::Debug>(MakeLogMessage(std::format("State: {}", static_cast<int>(self.state_))));
    ToLog<LogLevel::Debug>(MakeLogMessage(std::format("Content length: {}", static_cast<int>(self.content_length_))));
    ToLog<LogLevel::Debug>(MakeLogMessage(std::format("Method: {}, Path: {}, Version: {}", self.method_, self.path_, self.version_)));

    return HttpCode::NoRequest;
}

inline void HttpRequest::ParsePath(this HttpRequest &self) {
    if (self.path_ == "/") {
        self.path_ = "/index.html";
    } else if (DefaultHtml.contains(self.path_)) {
        self.path_ += ".html";
    }
}

inline HttpCode HttpRequest::ParseRequestLine(this HttpRequest &self, const std::string &line) {
    std::regex pattern{"^([^ ]*) ([^ ]*) HTTP/([^ ]*)$"};
    std::smatch sub_match;

    if (std::regex_match(line, sub_match, pattern)) {
        self.method_  = sub_match[1];
        self.path_    = sub_match[2];
        self.version_ = sub_match[3];
        self.state_   = ParseState::Headers;
        return HttpCode::NoRequest;
    }

    ToLog<LogLevel::Error>(MakeLogMessage("RequestLine Erro"));
    
    return HttpCode::BadRequest;
}

inline HttpCode HttpRequest::ParseHeader(this HttpRequest &self, const std::string& line) {
    std::regex pattern("^([^:]*): ?(.*)$");
    std::smatch sub_match;
    if (std::regex_match(line, sub_match, pattern)) {
        self.header_[sub_match[1]] = sub_match[2];
        if (sub_match[1] == "Connection")
            self.linger_ = (sub_match[2] == "keep-alive");
        if (sub_match[1] == "Content-Length") {
            self.content_length_ = stoi(sub_match[2]);
        }
        return HttpCode::NoRequest;
    } else if (self.content_length_) {
        self.state_ = ParseState::Body;
        return HttpCode::NoRequest;
    } else {
        return HttpCode::GetRequest;
    }
}

inline HttpCode HttpRequest::ParseBody(this HttpRequest &self) {
    if (self.method_ == "POST" && self.header_["Content-Type"] == "application/x-www-form-urlencoded")
    {
        self.ParseFromUrlEncoded();
        if (DefaultHtmlTag.contains(self.path_)) {
            int tag = DefaultHtmlTag.find(self.path_)->second;
            // LOG_DEBUG("Tag:%d", tag);
            ToLog<LogLevel::Debug>(MakeLogMessage(std::format("Tag: {}", tag)));
            if (UserVerify(self.post_["username"], self.post_["password"], tag))
            {
                ToLog<LogLevel::Info>(MakeLogMessage(std::format("User: {}, Password: {}, Success.", self.post_["username"], self.post_["password"])));
                self.path_ = "/welcome.html";
            }
            else
            {
                ToLog<LogLevel::Info>(MakeLogMessage(std::format("User: {}, Password: {}, Failed.", self.post_["username"], self.post_["password"])));
                self.path_ = "/error.html";
            }
        }
    }

    ToLog<LogLevel::Debug>(MakeLogMessage(std::format("Body: {}, Length: {}", self.body_, self.body_.length())));

    return HttpCode::GetRequest;
}

inline void HttpRequest::ParseFromUrlEncoded(this HttpRequest &self) {
    if (self.body_.empty())
        return;

    std::string key, value;
    int num = 0, n = self.body_.size();
    int i = 0, j = 0;
    for (; i < n; i ++) {
        if (auto ch = self.body_[i]; ch == '=') {
            key = self.body_.substr(j, i - j);
            j = i + 1;
        } else if (ch == '+') {
            self.body_[i] = ' ';
        } else if (ch == '%') {
            num = ConvertToHex(self.body_[i + 1] * 16 + ConvertToHex(self.body_[i + 2]));
            self.body_[i + 2] = num % 10 + '0';
            self.body_[i + 1] = num / 10 + '0';
            i += 2;
        } else if (ch == '&') {
            value = self.body_.substr(j, i - j);
            j = i + 1;
            self.post_[key] = value;
        } else{ 
            // wtf..
        }
    }

    assert(j <= i);
    if (!self.post_.count(key) && j < i) {
        value = self.body_.substr(j, i - j);
        self.post_[key] = value;
    }
}

inline bool HttpRequest::UserVerify(const std::string& name, const std::string& pwd, bool is_login) {
    if (name.empty() || pwd.empty() || name == "" || pwd == "") {
        return false; 
    }
    ToLog<LogLevel::Debug>(MakeLogMessage(std::format("Verify name: {}, pwd: {}", name, pwd)));
    
    MYSQL *sql;
    auto sql_guard = SqlConnect(&sql, SqlConnectPool::Instance());
    assert(sql);

    bool flag = !is_login;
    
    std::array<char, 256> order{};
    MYSQL_RES *mysql_result = nullptr;
    snprintf(order.data(), 256, "SELECT username, passwd FROM user WHERE username='%s' LIMIT 1", name.c_str());

    ToLog<LogLevel::Debug>(MakeLogMessage(std::format("SQL: {}", "SELECT username, passwd FROM user WHERE username='{}' LIMIT 1", name)));

    if(mysql_query(sql, order.data())) { 
        mysql_free_result(mysql_result);
        return false; 
    }
    mysql_result = mysql_store_result(sql);

    while(MYSQL_ROW row = mysql_fetch_row(mysql_result)) {
        ToLog<LogLevel::Debug>(MakeLogMessage(std::format("MYSQL ROW: {} {}", std::string_view{row[0]}, std::string_view{row[1]})));

        std::string password(row[1]);
        if(is_login) {
            if(pwd == password) {
                flag = true;
            } else {
                flag = false;
                ToLog<LogLevel::Debug>(MakeLogMessage("Log error"));
            }
        } else { 
            flag = false; 
            ToLog<LogLevel::Debug>(MakeLogMessage("User used"));
        }
    }

    mysql_free_result(mysql_result);

    if(!is_login && flag == true) {
        ToLog<LogLevel::Debug>(MakeLogMessage("Register"));
        order.fill(0);
        snprintf(order.data(), 256,"INSERT INTO user(username, passwd) VALUES('%s','%s')", name.c_str(), pwd.c_str());

        ToLog<LogLevel::Debug>(MakeLogMessage(std::format("SQL: INSERT INTO user(username, passwd) VALUES('{}','{}')", name, pwd)));

        if (mysql_query(sql, order.data())) { 
            ToLog<LogLevel::Debug>(MakeLogMessage("Insert error"));
            flag = false;
        } else {
            flag = true;
        }
    }

    ToLog<LogLevel::Debug>(MakeLogMessage("UserVerify success!!"));

    return flag;
}


} // namespace Koro
