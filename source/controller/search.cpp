#include <controller/search.hpp>

#include <drogon/orm/DbClient.h>
#include <drogon/orm/Result.h>
#include <dvb/resource_data.hpp>

namespace web
{
    void search::process(const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
            const std::string& input)
    {
        using namespace drogon::orm;

        drogon::app().getDbClient()->execSqlAsync(
            "select name, data from resource where name like '%$1%",
            [callback, input](const Result& result)
            {
                std::vector<dvb::resource_data> resources;
                resources.emplace_back(dvb::resource_data{ input, "type", "data" });

                for (auto row : result)
                {
                    resources.emplace_back(dvb::resource_data{ 
                        row["name"].as<std::string>(), 
                        "type", 
                        row["data"].as<std::string>() });

                }

                drogon::HttpViewData view_data;
                view_data.insert("title", "Searching " + input);
                view_data.insert("search_input", input);
                view_data.insert("resources", resources);

                auto resp = drogon::HttpResponse::newHttpViewResponse("views::search", view_data);
                callback(resp);
            },
            [](const DrogonDbException& e) {

            },
            input);
    }
} // web