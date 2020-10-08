#pragma once

#include <drogon/HttpController.h>

class search : public drogon::HttpController<search>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(search::process,"/search/{1}", drogon::Get);
        ADD_METHOD_TO(search::process2,"/zeta/", drogon::Get);
    METHOD_LIST_END

    void process(const drogon::HttpRequestPtr&,
                std::function<void (const drogon::HttpResponsePtr &)>&&,
                const std::string& input);   

    void process2(const drogon::HttpRequestPtr&,
            std::function<void (const drogon::HttpResponsePtr &)>&&);          
};
