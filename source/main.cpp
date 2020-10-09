#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>

int main()
{
    drogon::app().loadConfigFile("resource/config.json");

    auto clientPtr = drogon::app().getDbClient();

    constexpr auto resource_table = R"(
CREATE TABLE resource (
    id serial primary key,
    name varchar(255),
    data text,
);
    )";

    clientPtr->execSqlSync(create_table_resource);

    drogon::app().run();

    return 0;
}