#include <controller/resource.hpp>

#include <dvb/resource_data.hpp>

namespace web
{
    void resource::view_add(const drogon::HttpRequestPtr& req, std::function<void (const drogon::HttpResponsePtr &)>&& callback) const
    {
        drogon::HttpViewData view_data;

        view_data.insert("title", "Add a new resource");
        auto resp = drogon::HttpResponse::newHttpViewResponse("resource_add.csp", view_data);
        callback(resp);
    }

    void resource::add(dvb::resource_data&& resource_data, std::function<void(const drogon::HttpResponsePtr &)>&& callback) const
    {
        drogon::HttpViewData view_data;

        drogon::app().getDbClient()->execSqlSync(
            "insert into resource(name, data) VALUES($1, $2)", resource_data.name, resource_data.data);

        view_data.insert("title", "Add a new resource");
        view_data.insert("status", "Resource ' " + resource_data.name + " ' has been added");
        auto resp = drogon::HttpResponse::newHttpViewResponse("views::resource_add", view_data);
        callback(resp);
    }
} // web

namespace drogon
{
    template <>
    inline dvb::resource_data fromRequest(const HttpRequest& req)
    {
        auto input = req.getParameters();
        dvb::resource_data data;
        data.name = input["name"];
        data.type = input["type"];
        data.data = input["data"];

        return data;
    }
} // drogon