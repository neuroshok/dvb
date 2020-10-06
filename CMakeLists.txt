cmake_minimum_required(VERSION 3.13)
project(dvb)

set(CMAKE_CXX_STANDARD 17)

set(DVB_ROOT ${CMAKE_SOURCE_DIR})

# views
FILE(GLOB SCP_LIST ${CMAKE_CURRENT_SOURCE_DIR}/view/*.csp)
foreach(cspFile ${SCP_LIST})
    message(STATUS "cspFile:" ${cspFile})
    EXEC_PROGRAM(basename ARGS "-s .csp ${cspFile}" OUTPUT_VARIABLE classname)
    message(STATUS "view classname:" ${classname})
    add_custom_command(OUTPUT ${classname}.h ${classname}.cc
        COMMAND drogon_ctl
        ARGS create view ${cspFile}
        DEPENDS ${cspFile}
        VERBATIM )
   set(VIEWSRC ${VIEWSRC} ${classname}.cc)
endforeach()

add_executable(dvb source/main.cpp source/controller/search.cpp ${VIEWSRC})

# third_party
add_subdirectory(third_party/drogon)
target_link_libraries(dvb PRIVATE drogon)