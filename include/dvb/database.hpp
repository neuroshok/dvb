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
        owner_id integer NOT NULL,
        owner_type integer NOT NULL DEFAULT 0,
        name varchar(255) NOT NULL,
        shortname varchar(255),
        tags varchar(255),
        type integer NOT NULL,
        format integer NOT NULL,
        location integer,
        author varchar(255) NOT NULL DEFAULT 'anonymous',
        date timestamp,
        data text NOT NULL
    );)";

    static constexpr auto table_entity = R"(
    create table if not exists table_entity(
        id serial primary key,
        name integer,
        type integer
    );)";
} // dvb

#endif // INCLUDE_DVB_DATABASE_HPP_DVB
