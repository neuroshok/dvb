#ifndef INCLUDE_DVB_ERROR_HPP_DVB
#define INCLUDE_DVB_ERROR_HPP_DVB

#include <drogon/HttpResponse.h>

namespace dvb
{
    void error(std::function<void(const drogon::HttpResponsePtr&)>&& callback)
    {
        drogon::HttpViewData view_data;


        //callback();
    }
} // dvb

#endif // INCLUDE_DVB_ERROR_HPP_DVB
