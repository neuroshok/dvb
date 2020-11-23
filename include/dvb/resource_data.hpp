#pragma once

#include <dvb/type.hpp>

#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>

namespace dvb
{
    struct resource_data
    {
        int owner_id{};
        std::string name{};
        std::string shortname{};
        resource_type type{};
        resource_format format{};
        std::string tags{};
        std::string author{};
        std::string date{};
        std::string data{};

        static resource_data from_row(const drogon::orm::Row& row)
        {
            dvb::resource_data data;
            data.owner_id = row["owner_id"].as<int>();
            data.name = row["name"].as<std::string>();
            data.shortname = row["shortname"].as<std::string>();
            data.type = static_cast<dvb::resource_type>(row["type"].as<int>());
            data.format = static_cast<dvb::resource_format>(row["format"].as<int>());
            data.name = row["name"].as<std::string>();
            data.tags = row["tags"].as<std::string>();
            data.author = row["author"].as<std::string>();
            data.date = row["date"].as<std::string>();
            data.data = row["data"].as<std::string>();

            return data;
        }
    };
} // dvb