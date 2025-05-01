cmake_minimum_required(VERSION 3.23)

set(project "car")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
    car.cpp
)

set(${project}_HEADERS
    car.hpp
)

set(${project}_SOURCE_LIST
    ${${project}_SOURCES}
    ${${project}_HEADERS}
)

add_library(${project}
    STATIC
    ${${project}_SOURCE_LIST}
)
