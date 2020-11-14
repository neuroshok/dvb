#ifndef INCLUDE_DVB_USER_HPP_DVB
#define INCLUDE_DVB_USER_HPP_DVB

#include <string>

namespace dvb
{
    class user
    {
    public:
        user(std::string name = "anonymous")
            : name_{ std::move(name) }
            , logged_{ false }
        {}

        bool connect()
        {
            logged_ = true;
            return true;
        }

        const std::string& name() const { return name_; }
        bool is_logged() const { return logged_; }

    private:
        std::string name_;
        bool logged_;
    };
} // dvb

#endif // INCLUDE_DVB_USER_HPP_DVB
