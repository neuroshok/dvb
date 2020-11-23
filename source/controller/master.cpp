#include <controller/master.hpp>

#include <dvb/resource_data.hpp>
#include <dvb/user.hpp>
#include <dvb/view.hpp>

namespace web
{
    void master::home(const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback)
    {
        using namespace drogon::orm;

        drogon::app().getDbClient()->execSqlAsync(
            "select * from resource where true ORDER BY id desc LIMIT 10",
            [callback, &req](const Result& result)
            {
                std::vector<dvb::resource_data> resources;

                for (auto row : result)
                {
                    dvb::resource_data::from_row(row);

                    resources.emplace_back(dvb::resource_data::from_row(row));
                }

                dvb::view view_data{ req };
                view_data.insert("title", "Home");
                view_data.insert("resources", resources);

                auto resp = drogon::HttpResponse::newHttpViewResponse("view::search", view_data);
                callback(resp);
            },
            [](const DrogonDbException& e) {
                std::cout << e.base().what();
            });
    }
} // web