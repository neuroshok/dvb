#pragma once

#include <drogon/HttpController.h>

class search : public drogon::HttpController<search>
{
public:
    METHOD_LIST_BEGIN
        METHOD_ADD(search::process,"/?s={1}", drogon::Get);
        METHOD_ADD(search::process,"/{1}", drogon::Get);
    METHOD_LIST_END

    void process(const drogon::HttpRequestPtr&,
                std::function<void (const drogon::HttpResponsePtr &)>&&,
                const std::string& input);   
};