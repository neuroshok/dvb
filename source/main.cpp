#include <drogon/drogon.h>

int main()
{
    drogon::app().loadConfigFile("config.json");
    drogon::app()
    .setDocumentRoot("./app")
    .enableRunAsDaemon()
    .run();

    return 0;
}