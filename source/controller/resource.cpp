#include <controller/resource.hpp>
#include <dvb/resource_data.hpp>

void resource::add(dvb::resource_data&&, std::function<void(const drogon::HttpResponsePtr &)>&& callback) const
{
    drogon::HttpViewData view_data;

    std::vector<std::string> resources;
    view_data.insert("resources", resources);
    auto resp = drogon::HttpResponse::newHttpViewResponse("resource_add.csp", view_data);
    callback(resp);
}

namespace drogon
{
    template <>
    inline dvb::resource_data fromRequest(const HttpRequest& req)
    {
        auto json = req.getJsonObject();
        dvb::resource_data data;
        if(json)
        {
            data.name = (*json)["name"].asString();
            data.type = (*json)["type"].asString();
            data.data = (*json)["data"].asString();
        }
        return data;
    }
}