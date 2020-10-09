#include <controller/search.hpp>
#include <dvb/resource_data.hpp>

namespace web
{
    void search::process(const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
            const std::string& input)
    {
        drogon::HttpViewData view_data;

        std::vector<dvb::resource_data> resources;
        view_data.insert("title", "Searching " + input);
        view_data.insert("search_input", input);
        resources.emplace_back(dvb::resource_data{ "name", "type", "data" });
        resources.emplace_back(dvb::resource_data{ input, "type", "data" });
        resources.emplace_back(dvb::resource_data{ "title_test2222222222222", "type", "data" });

        view_data.insert("resources", resources);
        auto resp = drogon::HttpResponse::newHttpViewResponse("views::search", view_data);
        callback(resp);
    }
} // web