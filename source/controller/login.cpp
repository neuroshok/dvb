#include <controller/login.hpp>

#include <dvb/error.hpp>
#include <dvb/user.hpp>
#include <plugin/oauth.hpp>

namespace web
{
    void login::process(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback
                        , std::string&& provider)
    {
        drogon::app().getPlugin<OAuth>()->process(provider, callback);
    }

    void login::process_auth(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback
                            , std::string&& provider, std::string&& code, std::string&& state)
    {
        drogon::app().getPlugin<OAuth>()->process(provider, code, [callback, &req](bool success, const drogon::HttpResponsePtr& oauth_response)
        {
            if (success)
            {
                auto user_name = oauth_response->jsonObject()->get("login", "").asString();
                auto avatar_url = oauth_response->jsonObject()->get("avatar_url", "").asString();
                dvb::user user{ user_name };
                user.set_avatar_url(avatar_url);
                user.connect();
                req->session()->insert("user", std::move(user));
                auto response = drogon::HttpResponse::newHttpResponse();
                response->setStatusCode(drogon::HttpStatusCode::k303SeeOther);
                response->addHeader("Location", "/");
                callback(response);
            }
        });
    }
} // web