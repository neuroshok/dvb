#pragma once

#include <drogon/HttpController.h>

#include <string>

namespace web
{
    class login : public drogon::HttpController<login>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(login::process,"/login/oauth/{1}", drogon::Get);
            ADD_METHOD_TO(login::process_auth,"/login?provider={1}&code={2}&state={3}", drogon::Get);
        METHOD_LIST_END

        void process(const drogon::HttpRequestPtr&, std::function<void(const drogon::HttpResponsePtr&)>&&, std::string&& provider);
        void process_auth(const drogon::HttpRequestPtr&, std::function<void(const drogon::HttpResponsePtr&)>&&
                        , std::string&& provider, std::string&& code, std::string&& state);
    };
} // web