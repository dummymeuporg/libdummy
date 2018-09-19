cmake_minimum_required(VERSION 3.10.0)
project(dummy)
include_directories(include)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lopenssl")
add_library(dummy
	src/crypto/sha512.cpp
)
