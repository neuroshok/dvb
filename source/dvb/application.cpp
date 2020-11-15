#include <dvb/application.hpp>

namespace dvb
{
    application::application(const std::string& config_file)
        : version_{ "0.1.0" }
    {
        drogon::app().loadConfigFile(config_file);
        initialize_database();
    }

    void application::run() const
    {
        drogon::app().run();
    }

    const std::string& application::version() const
    {
        return version_;
    }

    void application::initialize_database() const
    {
        drogon::app().registerBeginningAdvice([this]()
        {
            drogon::app().getDbClient()->execSqlSync(dvb::database::table_system);

            bool update_required = false;
            auto result = drogon::app().getDbClient()->execSqlSync("select version from system");
            if (result.size())
            {
                auto db_version = result[0]["version"].as<std::string>();
                if (db_version != version()) update_database(db_version, version());
            }
            else make_database();
        });
    }

    void application::make_database() const
    {
        LOG_INFO << "make database";
        //drogon::app().getDbClient()->execSqlSync("drop table if exists entity");
        //drogon::app().getDbClient()->execSqlSync("drop table if exists resource");

        drogon::app().getDbClient()->execSqlSync("insert into system(version) values($1)", version_);

        drogon::app().getDbClient()->execSqlSync(dvb::database::table_entity);
        drogon::app().getDbClient()->execSqlSync(dvb::database::table_resource);
    }

    void application::update_database(const std::string& source, const std::string& target) const
    {
        LOG_FATAL << "update required from " << source << " to " << target;
    }
} // dvb
