cmake_minimum_required(VERSION 3.10.0)
project(dummy)
include_directories(include)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
    -lboost_system \
    -lcrypto -lssl")
add_library(dummy
    src/utils.cpp
	src/crypto/sha512.cpp
)


add_executable(sha512_tests
	tests/sha512_tests.cpp
)


target_link_libraries(
	sha512_tests
	dummy
)
