#ifndef INCLUDE_DVB_ERROR_HPP_DVB
#define INCLUDE_DVB_ERROR_HPP_DVB

#include <drogon/HttpResponse.h>
#include <string>

namespace dvb
{
    enum class errc
    {
        authentication_required
    };

    void error(std::function<void(const drogon::HttpResponsePtr&)> callback, errc code);
    void error(std::function<void(const drogon::HttpResponsePtr&)> callback, std::string message);
    void error404(std::function<void(const drogon::HttpResponsePtr&)> callback);
} // dvb

#endif // INCLUDE_DVB_ERROR_HPP_DVB
