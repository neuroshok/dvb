#ifndef INCLUDE_DVB_TYPE_HPP_DVB
#define INCLUDE_DVB_TYPE_HPP_DVB

namespace dvb
{
    enum class entity_type { user, organisation };
    enum class resource_type { article, community, course, project, other };
    enum class resource_format { text, image, video };
    enum class resource_location { local, remote };

    static std::array<std::string, 5> str_resource_type
    {
        "article", "community", "course", "project", "other"
    };

    inline std::string to_string(resource_type v)
    {
        auto index = static_cast<int>(v);
        return str_resource_type[index];
    }
} // dvb

#endif // INCLUDE_DVB_TYPE_HPP_DVB
