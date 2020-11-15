#ifndef INCLUDE_DVB_DATABASE_HPP_DVB
#define INCLUDE_DVB_DATABASE_HPP_DVB

namespace dvb::database
{
    enum class entity_type { user, organisation };
    enum class resource_type { article, course };
    enum class resource_format { text, image, video };
    enum class resource_location { local, remote };

    static constexpr auto table_system = R"(
    create table if not exists system(
        version varchar(24) not null
    );)";

    static constexpr auto table_resource = R"(
    create table if not exists resource(
        id serial primary key,
        owner_id integer,
        format integer,
        location integer,
        content text
    );)";

    static constexpr auto table_entity = R"(
    create table if not exists table_entity(
        id serial primary key,
        name integer,
        type integer
    );)";
} // dvb

#endif // INCLUDE_DVB_DATABASE_HPP_DVB
