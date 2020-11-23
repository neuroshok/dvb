#ifndef INCLUDE_DVB_USER_HPP_DVB
#define INCLUDE_DVB_USER_HPP_DVB

#include <drogon/HttpRequest.h>
#include <string>

namespace dvb
{
    class user
    {
    public:
        explicit user(uint64_t user_id = 0, std::string name = "anonymous")
            : id_{ user_id }
            , name_{ std::move(name) }
            , logged_{ false }
        {}

        void login() { logged_ = true; }
        void logout() { logged_ = false; }

        void set_avatar_url(std::string avatar_url) { avatar_url_ = std::move(avatar_url); }

        int id() const { return id_; }
        const std::string& name() const { return name_; }
        const std::string& avatar_url() const { return avatar_url_; }
        bool is_logged() const { return logged_; }

        static bool is_logged(const drogon::HttpRequestPtr& req)
        {
            if (req->session()->find("user") && req->session()->getRef<dvb::user>("user").is_logged()) return true;
            return false;
        }

        static dvb::user& get(const drogon::HttpRequestPtr& req)
        {
            if (!req->session()->find("user")) throw std::logic_error("session not found");
            return req->session()->getRef<dvb::user>("user");
        }

    private:
        int id_;
        std::string name_;
        std::string avatar_url_;
        bool logged_;
    };
} // dvb

#endif // INCLUDE_DVB_USER_HPP_DVB
