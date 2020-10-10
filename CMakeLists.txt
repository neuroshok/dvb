cmake_minimum_required(VERSION 3.13)
project(dvb)

set(CMAKE_CXX_STANDARD 17)

set(DVB_ROOT ${CMAKE_SOURCE_DIR})

# third_party
set(BUILD_EXAMPLES OFF)
add_subdirectory(third_party/drogon)
target_link_libraries(dvb PRIVATE drogon)

# views
file(MAKE_DIRECTORY ${DVB_ROOT}/generated/view)
file(GLOB SCP_LIST ${DVB_ROOT}/source/view/*.csp)

file(GLOB_RECURSE SCP_LIST ${CMAKE_CURRENT_SOURCE_DIR}/views/*.csp)
foreach(cspFile ${SCP_LIST})
  message(STATUS "cspFile:" ${cspFile})
   drogon_create_view(${cspFile} DVB_VIEWS TRUE)
endforeach()

#foreach(csp_file ${SCP_LIST})
#    message(STATUS "csp_file:" ${csp_file})
#    EXEC_PROGRAM(basename ARGS "-s .csp ${csp_file}" OUTPUT_VARIABLE classname)
#    message(STATUS "view classname:" ${classname})
#    add_custom_command(OUTPUT ${DVB_ROOT}/generated/view/${classname}.h ${DVB_ROOT}/generated/view/${classname}.cc
#        COMMAND drogon_ctl
#        ARGS create view ${csp_file} -n views
#        DEPENDS ${csp_file}
#        WORKING_DIRECTORY ${DVB_ROOT}/generated/view
#        VERBATIM)
#
#    set(DVB_VIEWS ${DVB_VIEWS} ${DVB_ROOT}/generated/view/${classname}.cc)
#endforeach()

file(GLOB_RECURSE DVB_SOURCES
        "source/*.cpp"
        "include/*.hpp")

add_executable(dvb ${DVB_SOURCES} ${DVB_VIEWS})
add_dependencies(dvb drogon_ctl)
target_include_directories(dvb PUBLIC include)

if (NOT DVB_OUTPUT)
    set(DVB_OUTPUT ${CMAKE_BINARY_DIR}/${DVB_OUTPUT})
endif()

set_target_properties(dvb PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${DVB_OUTPUT}
)

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