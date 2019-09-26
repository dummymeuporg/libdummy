cmake_minimum_required(VERSION 3.10.0)
project(dummy)
include_directories(include)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.69.0 REQUIRED)
find_package(Lua51 REQUIRED)

add_definitions(-D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING)

macro(GroupSources curdir)
    file(
        GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
        ${PROJECT_SOURCE_DIR}/${curdir}/*
    )
    foreach(child ${children})
        if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            GroupSources(${curdir}/${child})
        else()
            string(REPLACE "/" "\\" groupname ${curdir})
            source_group(
                ${groupname}
                FILES
                ${PROJECT_SOURCE_DIR}/${curdir}/${child}
            )
        endif()
    endforeach()
endmacro()

link_directories(${Boost_LIBRARY_DIRS})

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/dummy/*.hpp")

GroupSources(include/dummy)
GroupSources(src)

add_library(dummy STATIC ${SOURCES} ${HEADERS})

target_include_directories(dummy PUBLIC ${Boost_INCLUDE_DIR} ${LUA_INCLUDE_DIR})


#add_executable(sha512_tests
#	tests/sha512_tests.cpp
#)


set(PROJECT_TEST_LIBRARIES dummy ${Boost_LIBRARIES})
if (UNIX)
    set(PROJECT_TEST_LIBRARIES
        ${PROJECT_TEST_LIBRARIES}
        stdc++fs
    )
endif (UNIX)

add_executable(project_tests
    tests/core/project_tests.cpp
)

add_executable(outgoing_packet_tests
    tests/protocol/outgoing_packet_tests.cpp
)

add_executable(incoming_packet_tests
    tests/protocol/incoming_packet_tests.cpp
)

add_executable(character_tests
    tests/core/character_tests.cpp
)

add_executable(character_read_file_tests
    tests/core/character_read_file_tests.cpp
)

#target_link_libraries(
#	sha512_tests
#	dummy
#)


target_link_libraries(
    project_tests
    ${PROJECT_TEST_LIBRARIES}
)

target_link_libraries(
    outgoing_packet_tests
    dummy
)

target_link_libraries(
    incoming_packet_tests
    dummy
)

target_link_libraries(
    character_tests
    dummy
)


target_link_libraries(
    character_read_file_tests
    dummy
)
