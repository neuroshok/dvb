#include <controller/user.hpp>

#include <dvb/error.hpp>
#include <dvb/user.hpp>
#include <plugin/oauth.hpp>

namespace web
{
    void user::login(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback
                        , std::string&& provider)
    {
        drogon::app().getPlugin<OAuth>()->process(provider, callback);
    }

    void user::logout(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback)
    {
        dvb::user::get(req).logout();

        auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::HttpStatusCode::k303SeeOther);
        response->addHeader("Location", "/");
        callback(response);
    }

    void user::process_auth(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback
                            , std::string&& provider, std::string&& code, std::string&& state)
    {
        drogon::app().getPlugin<OAuth>()->process(provider, code, [callback, &req](bool success, std::string token, const drogon::HttpResponsePtr& oauth_response)
        {
            if (success)
            {
                auto user_id = oauth_response->jsonObject()->get("id", 0).asUInt64();
                auto user_name = oauth_response->jsonObject()->get("login", "").asString();
                auto avatar_url = oauth_response->jsonObject()->get("avatar_url", "").asString();

                if (!req->session()->find("user"))
                {
                    dvb::user user{ user_id, user_name };
                    user.set_avatar_url(avatar_url);
                    user.login();
                    req->session()->insert("user", std::move(user));
                }
                else dvb::user::get(req).login();

                // get user orgs
                auto client = drogon::HttpClient::newHttpClient("https://api.github.com");
                auto user_req = drogon::HttpRequest::newHttpRequest();
                user_req->setMethod(drogon::Get);
                user_req->addHeader("Accept", "application/vnd.github.v3+json");
                user_req->addHeader("Authorization", "token " + token);
                user_req->setPath("/user/orgs");

                client->sendRequest(user_req, [callback](drogon::ReqResult result, const drogon::HttpResponsePtr& user_response)
                {
                    if (result != drogon::ReqResult::Ok) LOG_ERROR << "can't get user orgs";

                    for (size_t i = 0; i < user_response->getJsonObject()->size(); ++i)
                    {
                        LOG_ERROR << user_response->getJsonObject()->get(i, "").get("login", "").asString() << "\n";
                    }

                    auto response = drogon::HttpResponse::newHttpResponse();
                    response->setStatusCode(drogon::HttpStatusCode::k303SeeOther);
                    response->addHeader("Location", "/");
                    callback(response);
                });
            }
        });
    }
} // web