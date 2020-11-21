#ifndef INCLUDE_DVB_DATABASE_HPP_DVB
#define INCLUDE_DVB_DATABASE_HPP_DVB

namespace dvb::database
{
    static constexpr auto table_system = R"(
    create table if not exists system(
        version varchar(24) not null
    );)";

    static constexpr auto table_tag = R"(
    create table if not exists tag(
        id serial primary key,
        owner_id integer,
        name varchar(255),
        format integer,
        location integer,
        data text
    );)";

    static constexpr auto table_resource = R"(
    create table if not exists resource(
        id serial primary key,
        owner_id integer,
        name varchar(255),
        description varchar(255),
        tag integer,
        format integer,
        location integer,
        data text
    );)";

    static constexpr auto table_entity = R"(
    create table if not exists table_entity(
        id serial primary key,
        name integer,
        type integer
    );)";
} // dvb

#endif // INCLUDE_DVB_DATABASE_HPP_DVB
