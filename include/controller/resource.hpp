#pragma once

#include <drogon/HttpController.h>

namespace dvb
{
    struct resource_data;
} // dvb

namespace web
{
    class resource : public drogon::HttpController<resource>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(resource::view_add,"/resource/add", drogon::Get);
            ADD_METHOD_TO(resource::add,"/resource/add", drogon::Post);
        METHOD_LIST_END

        void view_add(const drogon::HttpRequestPtr&, std::function<void (const drogon::HttpResponsePtr&)>&&) const;
        void add(dvb::resource_data&&, std::function<void(const drogon::HttpResponsePtr&)>&&) const;
    };
} // web

namespace drogon
{
    //template <>
    //inline dvb::resource_data fromRequest(const HttpRequest&);
} // drogon