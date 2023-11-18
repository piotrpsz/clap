cmake_minimum_required(VERSION 3.26)
project(clap)

set(CMAKE_CXX_STANDARD 20)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(fmt REQUIRED)

add_library(clap STATIC
        clap.cpp clap.h
        argument.cpp argument.h
)
target_include_directories(clap PUBLIC fmt)
target_link_libraries(clap PUBLIC fmt::fmt)
