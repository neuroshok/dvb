#include <controller/master.hpp>

void master::home(const drogon::HttpRequestPtr& req,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    drogon::HttpViewData view_data;

    std::vector<std::string> resources;
    view_data.insert("title", "Home");

    auto resp = drogon::HttpResponse::newHttpViewResponse("main.csp", view_data);
    callback(resp);
}