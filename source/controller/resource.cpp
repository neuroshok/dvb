#include <controller/resource.hpp>

#include <drogon/orm/DbClient.h>

#include <dvb/resource_data.hpp>
#include <dvb/view.hpp>
#include <dvb/error.hpp>

namespace web
{
    void resource::view_add(const drogon::HttpRequestPtr& req, std::function<void (const drogon::HttpResponsePtr &)>&& callback) const
    {
        if (!dvb::user::is_logged(req)) return dvb::error(callback, dvb::errc::authentication_required);

        dvb::view view_data{ req };

        view_data.insert("title", "Add a new resource");
        auto resp = drogon::HttpResponse::newHttpViewResponse("view::resource_add", view_data);
        callback(resp);
    }

    void resource::add(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr &)>&& callback, dvb::resource_data&& resource_data) const
    {
        if (!dvb::user::is_logged(req)) return dvb::error(callback, dvb::errc::authentication_required);

        dvb::view view_data{ req };

        drogon::app().getDbClient()->execSqlSync(
            "insert into resource(owner_id, owner_type, name, shortname, type, format, tags, author, date, data) VALUES($1, $2, $3, $4, $5, $6, $7, $8, now(), $9)"
        , dvb::user::get(req).id()
        , static_cast<int>(dvb::entity_type::user)
        , resource_data.name
        , resource_data.shortname
        , static_cast<int>(resource_data.type)
        , static_cast<int>(resource_data.format)
        , resource_data.tags
        , resource_data.author
        , resource_data.data);

        view_data.insert("title", "Add a new resource");
        view_data.insert("status", "Resource <strong>" + resource_data.name + "</strong> has been added");
        auto resp = drogon::HttpResponse::newHttpViewResponse("view::resource_add", view_data);
        callback(resp);
    }

    void resource::get(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback, std::string&& short_name) const
    {
        dvb::view view_data{ req };

        drogon::app().getDbClient()->execSqlAsync(
            "select * from resource where shortname=$1",
            [callback, short_name, &req](const drogon::orm::Result& result)
            {
                std::vector<dvb::resource_data> resources;

                for (auto row : result)
                {
                    dvb::resource_data::from_row(row);

                    resources.emplace_back(dvb::resource_data::from_row(row));
                }

                dvb::view view_data{ req };
                view_data.insert("title", short_name);
                view_data.insert("resources", resources);

                auto resp = drogon::HttpResponse::newHttpViewResponse("view::search", view_data);
                callback(resp);
            },
            [](const drogon::orm::DrogonDbException& e) {
                std::cout << e.base().what();
            },
            short_name);
    }
} // web

namespace drogon
{
    template <>
    inline dvb::resource_data fromRequest(const HttpRequest& req)
    {
        auto input = req.getParameters();
        dvb::resource_data data;
        data.name = input["name"];
        data.shortname = input["shortname"];
        data.type = static_cast<dvb::resource_type>(std::stoi(input["type"]));
        data.format = static_cast<dvb::resource_format>(std::stoi(input["format"]));
        data.tags = input["tags"];
        data.author = input["author"];
        data.date = input["date"];
        data.data = input["data"];

        return data;
    }
} // drogon