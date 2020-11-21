#ifndef INCLUDE_PLUGIN_OAUTH_HPP_DVB
#define INCLUDE_PLUGIN_OAUTH_HPP_DVB

#include <drogon/drogon.h>

#include <string>

class OAuth : public drogon::Plugin<OAuth>
{
public:
    void initAndStart(const Json::Value& config) override;
    void shutdown() override;

    void process(std::string provider, std::function<void(const drogon::HttpResponsePtr&)> callback);
    void process(std::string provider, std::string code, std::function<void(bool, std::string, const drogon::HttpResponsePtr&)> callback);

private:
    std::string client_id_;
    std::string client_secret_;
};

#endif // INCLUDE_PLUGIN_OAUTH_HPP_DVB