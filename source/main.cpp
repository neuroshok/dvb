#include <drogon/drogon.h>

int main()
{
    drogon::app().loadConfigFile("resource/config.json");
    drogon::app().run();

    return 0;
}

app/data/style
app/view/
app/controller