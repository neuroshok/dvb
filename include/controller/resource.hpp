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
        METHOD_ADD(resource::view_add,"/add", drogon::Get);
        METHOD_ADD(resource::add,"/add", drogon::Post);
    METHOD_LIST_END

    void view_add(const drogon::HttpRequestPtr&, std::function<void (const drogon::HttpResponsePtr&)>&&) const;
    void add(dvb::resource_data&&, std::function<void(const drogon::HttpResponsePtr&)>&&) const;
};
