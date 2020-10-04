#include <drogon/drogon.h>
using namespace drogon;
int main()
{
    drogon::app().loadConfigFile("config.json");
    drogon::app().run();
}