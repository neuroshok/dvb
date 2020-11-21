#include <dvb/error.hpp>

#include <string>

namespace dvb
{
    void error(std::function<void(const drogon::HttpResponsePtr&)> callback, errc code)
    {
        using namespace std::string_literals;

        switch (code)
        {
        case errc::authentication_required:
            error(callback, "Authentication required"s);
        }
    }

    void error(std::function<void(const drogon::HttpResponsePtr&)> callback, std::string message)
    {
        drogon::HttpViewData view_data;

        view_data.insert("title", "Error");
        view_data.insert("message", std::move(message));
        auto response = drogon::HttpResponse::newHttpViewResponse("view::error", view_data);

        response->setStatusCode(drogon::HttpStatusCode::k404NotFound);
        callback(response);
    }

    void error404(std::function<void(const drogon::HttpResponsePtr&)> callback)
    {
        auto response = drogon::HttpResponse::newHttpViewResponse("");
        response->setStatusCode(drogon::HttpStatusCode::k404NotFound);

        callback(response);
    }
} // dvb