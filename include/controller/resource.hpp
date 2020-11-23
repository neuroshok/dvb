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
            ADD_METHOD_TO(resource::get,"/r/{1}", drogon::Get);
        METHOD_LIST_END

        void view_add(const drogon::HttpRequestPtr&, std::function<void (const drogon::HttpResponsePtr&)>&&) const;
        void add(const drogon::HttpRequestPtr&, std::function<void(const drogon::HttpResponsePtr&)>&&, dvb::resource_data&& resource_data) const;
        void get(const drogon::HttpRequestPtr&, std::function<void(const drogon::HttpResponsePtr&)>&&, std::string&& short_name) const;
    };
} // web

namespace drogon
{
    //template <>
    //inline dvb::resource_data fromRequest(const HttpRequest&);
} // drogon