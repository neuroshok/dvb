#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>

int main()
{
    drogon::app().loadConfigFile("resource/config.json");
    drogon::app().run();

    return 0;
}