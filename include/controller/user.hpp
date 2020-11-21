#pragma once

#include <drogon/HttpController.h>

#include <string>

namespace web
{
    class user : public drogon::HttpController<user>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(user::login,"/login/oauth/{1}", drogon::Get);
            ADD_METHOD_TO(user::logout,"/logout", drogon::Get);
            ADD_METHOD_TO(user::process_auth,"/login?provider={1}&code={2}&state={3}", drogon::Get);
        METHOD_LIST_END

        void login(const drogon::HttpRequestPtr&, std::function<void(const drogon::HttpResponsePtr&)>&&, std::string&& provider);
        void logout(const drogon::HttpRequestPtr&, std::function<void(const drogon::HttpResponsePtr&)>&&);
        void process_auth(const drogon::HttpRequestPtr&, std::function<void(const drogon::HttpResponsePtr&)>&&
                        , std::string&& provider, std::string&& code, std::string&& state);
    };
} // web