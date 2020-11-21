#ifndef INCLUDE_DVB_TYPE_HPP_DVB
#define INCLUDE_DVB_TYPE_HPP_DVB

namespace dvb
{
    enum class entity_type { user, organisation };
    enum class resource_type { article, course, library };
    enum class resource_format { text, image, video };
    enum class resource_location { local, remote };
} // dvb

#endif // INCLUDE_DVB_TYPE_HPP_DVB
