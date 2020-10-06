#include <controller/search.hpp>

void search::process(const HttpRequestPtr &req,
           std::function<void (const HttpResponsePtr &)> &&callback,
           const std::string& input)
{
    LOG_DEBUG<<"search "<<input;

    HttpViewData view_data;

    std::vector<std::string> resources;
    view_data.insert("title","dvb title");
    resources.push_back("blablabla");
    resources.push_back("title_test2222222222222");
    resources.push_back("blablablablablablablablablablablablablablablablablablablablablablablabla");

    view_data.insert("resources", resources);
    auto resp=HttpResponse::newHttpViewResponse("search.csp", view_data);
    callback(resp);
}