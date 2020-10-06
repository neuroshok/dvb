#pragma once

#include <drogon/HttpController.h>

using namespace drogon;
namespace dvb
{
    namespace v1
    {
        class search : public drogon::HttpController<search>
        {
        public:
            METHOD_LIST_BEGIN
                //use METHOD_ADD to add your custom processing function here;
                METHOD_ADD(search::process,"/{1}", Post);
            METHOD_LIST_END
            //your declaration of processing function maybe like this:
            void process(const HttpRequestPtr &req,
                       std::function<void (const HttpResponsePtr &)> &&callback,
                       const std::string& input);
        };
    }
}