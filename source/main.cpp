#include <drogon/drogon.h>

int main()
{
    drogon::app().loadConfigFile("resource/config.json");
    drogon::app().run();

    auto clientPtr = drogon::app().getDbClient();

    constexpr auto resource_table = R"(
CREATE TABLE resource (
    id int,
    name varchar(255),
    data text,
);
    )";

    clientPtr->execSqlAsync(resource_table,
                            [](const Result &r) {
                                
                            },
                            [](const DrogonDbException& e) {
                                std::cerr << "error:" << e.base().what() << std::endl;
                            },
                            "dvb");

    return 0;
}