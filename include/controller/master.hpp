#pragma once

#include <drogon/HttpController.h>

namespace web
{
    class master : public drogon::HttpController<master>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(master::home,"/", drogon::Get);
        METHOD_LIST_END

        void home(const drogon::HttpRequestPtr&, std::function<void(const drogon::HttpResponsePtr &)>&&);
    };
} // web