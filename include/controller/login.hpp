#pragma once

#include <drogon/HttpController.h>

namespace web
{
    class login : public drogon::HttpController<GetEventLogInformation>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(login::process,"/login/oauth/{1}", drogon::Get);
        METHOD_LIST_END

        void process(const drogon::HttpRequestPtr&, std::function<void(const drogon::HttpResponsePtr&)>&&
        std::string oauth_service);
    };
} // web