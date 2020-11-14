#ifndef INCLUDE_DVB_VIEW_HPP_DVB
#define INCLUDE_DVB_VIEW_HPP_DVB

#include <drogon/HttpViewData.h>
#include <drogon/HttpRequest.h>

#include <dvb/user.hpp>

namespace dvb
{
    class view : public drogon::HttpViewData
    {
    public:
        explicit view(const drogon::HttpRequestPtr& req)
        {
            if (req->session()->find("user")) insert("user", req->session()->get<dvb::user>("user"));
        }
    };
} // dvb

#endif // INCLUDE_DVB_VIEW_HPP_DVB
