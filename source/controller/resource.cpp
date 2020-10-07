#include <controller/resource.hpp>

void resource::add(dvb::resource_data&&, std::function<void(const drogon::HttpResponsePtr &)>&&) const
{
    drogon::HttpViewData view_data;

    std::vector<std::string> resources;
    view_data.insert("resources", resources);
    auto resp = drogon::HttpResponse::newHttpViewResponse("resource_add.csp", view_data);
    callback(resp);
}