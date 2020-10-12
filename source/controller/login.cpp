#include <controller/login.hpp>
#include <oauth.hpp>

namespace web
{
    void login::process(const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback
            std::string oauth_provider)
    {
        drogon::app().getPlugin<OAuth>().process(oauth_service, [callback]()
        {
            std::cout << "login cb";
            drogon::HttpViewData view_data;
            view_data.insert("title", "Auth");
            auto resp = drogon::HttpResponse::newHttpViewResponse("view::main", view_data);
            callback(resp);
        });
    }
} // web