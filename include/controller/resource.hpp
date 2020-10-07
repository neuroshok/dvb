#pragma once

#include <drogon/HttpController.h>

namespace dvb
{
    struct resource_data;
} // dvb

class resource : public drogon::HttpController<resource>
{
public:
    METHOD_LIST_BEGIN
        METHOD_ADD(resource::add,"/", drogon::Post);
    METHOD_LIST_END

    void add(dvb::resource_data&&, std::function<void(const drogon::HttpResponsePtr &)>&&) const;
};

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
};
