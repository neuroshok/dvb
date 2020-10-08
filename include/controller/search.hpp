#pragma once

#include <drogon/HttpController.h>

class search : public drogon::HttpController<search>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(search::process,"/search/{1}", drogon::Get);
        ADD_METHOD_TO(search::process2,"/zeta/", drogon::Get);
        ADD_METHOD_TO(search::test,"/test/", drogon::Get);
    METHOD_LIST_END

    void process(const drogon::HttpRequestPtr&,
                std::function<void (const drogon::HttpResponsePtr &)>&&,
                const std::string& input);   

    void process2(const drogon::HttpRequestPtr&,
            std::function<void (const drogon::HttpResponsePtr &)>&&);     

            
    void test(const drogon::HttpRequestPtr&, std::function<void (const drogon::HttpResponsePtr&)>&& callback) const
    {
        drogon::HttpViewData view_data;

        view_data.insert("title", "test");
        auto resp = drogon::HttpResponse::newHttpViewResponse("resource_add.csp", view_data);
        callback(resp);
    }     
};
