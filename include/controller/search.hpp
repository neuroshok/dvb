#pragma once

#include <drogon/HttpController.h>

class search : public drogon::HttpController<search>
{
public:
    METHOD_LIST_BEGIN
        METHOD_ADD(search::process,"/{1}", drogon::Get);
        METHOD_ADD(search::view_add,"/add/", drogon::Get);
    METHOD_LIST_END

    void process(const drogon::HttpRequestPtr &req,
                std::function<void (const drogon::HttpResponsePtr &)> &&callback,
                const std::string& input);

    void view_add(const drogon::HttpRequestPtr&, std::function<void (const drogon::HttpResponsePtr&)>&& callback) const
    {
            drogon::HttpViewData view_data;

        view_data.insert("title", "Add a new resource");
        auto resp = drogon::HttpResponse::newHttpViewResponse("resource_add.csp", view_data);
        callback(resp);
    }  
};
