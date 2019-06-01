cmake_minimum_required(VERSION 3.10.0)
project(dummy)
include_directories(include)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS system REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

add_library(dummy STATIC ${SOURCES} ${HEADERS})


#add_executable(sha512_tests
#	tests/sha512_tests.cpp
#)

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
    dummy
    boost_filesystem
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
