cmake_minimum_required(VERSION 3.13)
project(dvb)

set(CMAKE_CXX_STANDARD 17)

set(DVB_ROOT ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE DVB_SOURCES
        "source/*.cpp"
        "include/*.hpp")

add_executable(dvb ${DVB_SOURCES})
add_dependencies(dvb drogon_ctl)
target_include_directories(dvb PUBLIC include)

if (NOT DVB_OUTPUT)
    set(DVB_OUTPUT ${CMAKE_BINARY_DIR}/${DVB_OUTPUT})
endif()

set_target_properties(dvb PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${DVB_OUTPUT}
)

# third_party
set(BUILD_EXAMPLES OFF)
add_subdirectory(third_party/drogon)
target_link_libraries(dvb PRIVATE drogon)
drogon_create_views(dvb ${DVB_ROOT}/source/view/ ${DVB_ROOT}/generated/view true)


# copy app data
add_custom_command(
    TARGET dvb POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${DVB_ROOT}/app ${DVB_OUTPUT}/app
    COMMENT "Copy ${DVB_ROOT}/app to ${DVB_OUTPUT}/app")

# copy server resources
add_custom_command(
    TARGET dvb POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${DVB_ROOT}/resource ${DVB_OUTPUT}/resource
    COMMENT "Copy ${DVB_ROOT}/resource to ${DVB_OUTPUT}/resource")

    # restart // make custom target
    add_custom_command(
        TARGET dvb POST_BUILD
        #COMMAND pkill dvb
        #COMMAND ./dvb
        WORKING_DIRECTORY ${DVB_OUTPUT}
        COMMENT "Restart dvb")