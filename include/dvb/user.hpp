#ifndef INCLUDE_DVB_USER_HPP_DVB
#define INCLUDE_DVB_USER_HPP_DVB

#include <string>

namespace dvb
{
    class user
    {
    public:
        explicit user(std::string name = "anonymous")
            : name_{ std::move(name) }
            , logged_{ false }
        {}

        bool connect()
        {
            logged_ = true;
            return true;
        }

        void set_avatar_url(std::string avatar_url) { avatar_url_ = std::move(avatar_url); }

        const std::string& name() const { return name_; }
        const std::string& avatar_url() const { return avatar_url_; }
        bool is_logged() const { return logged_; }

    private:
        std::string name_;
        std::string avatar_url_;
        bool logged_;
    };
} // dvb

#endif // INCLUDE_DVB_USER_HPP_DVB
