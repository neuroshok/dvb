#include <controller/search.hpp>

#include <drogon/orm/DbClient.h>
#include <drogon/orm/Result.h>

#include <dvb/view.hpp>
#include <dvb/resource_data.hpp>

namespace web
{
    void search::process(const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
            const std::string& input)
    {
        using namespace drogon::orm;

        drogon::app().getDbClient()->execSqlAsync(
            "select * from resource where lower(name) like lower($1) LIMIT 100",
            [callback, &input, &req](const Result& result)
            {
                std::vector<dvb::resource_data> resources;

                for (auto row : result)
                {
                    dvb::resource_data::from_row(row);

                    resources.emplace_back(dvb::resource_data::from_row(row));
                }

                dvb::view view_data{ req };
                view_data.insert("title", "Searching " + input);
                view_data.insert("search_input", input);
                view_data.insert("resources", resources);

                auto resp = drogon::HttpResponse::newHttpViewResponse("view::search", view_data);
                callback(resp);
            },
            [](const DrogonDbException& e) {
                std::cout << e.base().what();
            },
            "%" + input + "%");
    }
} // web