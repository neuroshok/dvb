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
    void process(std::string provider, std::string code, std::function<void(bool, const drogon::HttpResponsePtr&)> callback);
};

// oauth.process<OAuth::Github>(client_id, []{})

        // https://github.com/login/oauth/authorize?client_id=ab36f70bc522920f7800&state=rng&login=ads00&scope=read:user
        // https://github.com/login/oauth/access_token
        /*
        client_id	string	Required. The client ID you received from GitHub for your GitHub App.
client_secret	string	Required. The client secret you received from GitHub for your GitHub App.
    44e4f8139ffc83f7ece7182ef3721b0c140c6cc7
code	string	Required. The code you received as a response to Step 1.
redirect_uri	string	The URL in your application where users are sent after authorization.
state	string	The unguessable random string you provided in Step 1.
*/
// GET /users/ads00 access_token=

#endif // INCLUDE_PLUGIN_OAUTH_HPP_DVB