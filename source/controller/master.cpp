#include <controller/master.hpp>

#include <dvb/view.hpp>
#include <dvb/user.hpp>

namespace web
{
    void master::home(const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback)
    {
        dvb::view view_data{ req };

        view_data.insert("title", "Home");

        auto resp = drogon::HttpResponse::newHttpViewResponse("view::main", view_data);
        callback(resp);
    }
} // web