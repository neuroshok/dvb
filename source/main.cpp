#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>

int main()
{
    drogon::app().loadConfigFile("resource/config.json");

    drogon::app().createDbClient("postgresql", "127.0.0.1", 5432, "dvb", "dvb", "dvbpass").run();

    return 0;
}