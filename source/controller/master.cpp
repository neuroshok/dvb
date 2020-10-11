#include <controller/master.hpp>

namespace web
{
    void master::home(const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback)
    {
        drogon::HttpViewData view_data;

        std::vector<std::string> resources;
        view_data.insert("title", "Home");

         drogon::app().getDbClient()->execSqlSync(
            "insert into resource(name, data) VALUES($1, $2)", "resource_data.name", "resource_data.data");


        auto resp = drogon::HttpResponse::newHttpViewResponse("view::main", view_data);
        callback(resp);
    }
} // web