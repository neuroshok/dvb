#pragma once

#include <drogon/HttpController.h>

namespace web
{
    class search : public drogon::HttpController<search>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(search::process,"/search/?s={1}", drogon::Get);
            ADD_METHOD_TO(search::process,"/search/{1}", drogon::Get);
        METHOD_LIST_END

        void process(const drogon::HttpRequestPtr&,
                    std::function<void (const drogon::HttpResponsePtr &)>&&,
                    const std::string& input);   
    };
} // web