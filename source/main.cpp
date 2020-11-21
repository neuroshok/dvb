#include <dvb/application.hpp>

int main()
{
    dvb::application app{ "resource/config.json" };

    app.run();

    return 0;
}

//domain/security language/cpp library

/discord/cpp