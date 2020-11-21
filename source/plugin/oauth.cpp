#include <plugin/oauth.hpp>


void OAuth::initAndStart(const Json::Value& config)
{
    client_id_ = config.get("client_id", "").asString();
    client_secret_ = config.get("client_secret", "").asString();
}

void OAuth::shutdown() {}

void OAuth::process(std::string provider, std::function<void(const drogon::HttpResponsePtr&)> callback)
{
    auto client = drogon::HttpClient::newHttpClient("https://github.com");
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::Get);
    req->setPath("/login/oauth/authorize");
    req->setParameter("client_id", client_id_);
    req->setParameter("state", "rng");
    req->setParameter("scope", "read:user,admin:org");

    client->sendRequest(req, [callback](drogon::ReqResult result, const drogon::HttpResponsePtr& response)
    {
        callback(response);
    });
}
void OAuth::process(std::string provider, std::string code, std::function<void(bool, std::string, const drogon::HttpResponsePtr&)> callback)
{
    LOG_DEBUG << "process code";
    auto client = drogon::HttpClient::newHttpClient("https://github.com");
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::Get);
    req->addHeader("Accept", "application/json");
    req->setPath("/login/oauth/access_token");
    req->setParameter("client_id", client_id_);
    req->setParameter("client_secret", client_secret_);
    req->setParameter("scope", "read:user,admin:org");
    req->setParameter("code", code);

    client->sendRequest(req, [callback](drogon::ReqResult result, const drogon::HttpResponsePtr& response)
    {
        if (result != drogon::ReqResult::Ok) LOG_ERROR << "OAuth process error";
        auto token = response->getJsonObject()->get("access_token", "").asString();

        if (std::empty(token)) callback(false, "", {});
        else
        {
            auto client = drogon::HttpClient::newHttpClient("https://api.github.com");
            auto req = drogon::HttpRequest::newHttpRequest();
            req->setMethod(drogon::Get);
            req->addHeader("Accept", "application/vnd.github.v3+json");
            req->addHeader("Authorization", "token " + token);
            req->setPath("/user");

            client->sendRequest(req, [callback, token = std::move(token)](drogon::ReqResult result, const drogon::HttpResponsePtr& response)
            {
                if (!std::empty(token)) callback(true, token, response);
            });
        }
    });
}