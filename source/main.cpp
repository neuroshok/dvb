#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>

int main()
{
    drogon::app().loadConfigFile("resource/config.json");

        //app().registerBeginningAdvice([]() {
       //Here the current thread is main event loop thread, and it's valid for fast database client, so we could get it here.
       //auto dptr = app().getFastDbClient("postgresql_client");
       //*aptr << "select ...." ...;
    //});

    drogon::app().run();




    return 0;
}