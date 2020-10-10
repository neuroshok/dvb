#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>

int main()
{
    drogon::app().loadConfigFile("resource/config.json");

    auto db = newPgClient("default", 1);

    constexpr auto create_table_resource = R"(
CREATE TABLE resource (
    id serial primary key,
    name varchar(255),
    data text,
);
    )";

    db->execSqlSync(create_table_resource);

    drogon::app().run();

    return 0;
}