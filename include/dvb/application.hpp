#ifndef INCLUDE_DVB_APPLICATION_HPP_DVB
#define INCLUDE_DVB_APPLICATION_HPP_DVB

#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>

#include <dvb/database.hpp>

namespace dvb
{
    class application
    {
    public:
        application(const std::string& config_file);

        void run() const;

        const std::string& version() const;

    private:
        void initialize_database() const;
        void make_database() const;
        void update_database(const std::string& source, const std::string& target) const;

    private:
        std::string version_;
    };
} // dvb

#endif // INCLUDE_DVB_APPLICATION_HPP_DVB