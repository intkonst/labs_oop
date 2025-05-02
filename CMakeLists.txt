cmake_minimum_required(VERSION 3.23)

set(project "lab_3")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
    main.cpp
    src/app.cpp
)

set(${project}_HEADERS
    src/app.hpp
)

add_subdirectory(fraction)

set(${project}_SOURCE_LIST
    ${${project}_SOURCES}
    ${${project}_HEADERS}
)

add_executable(${project}
    ${${project}_SOURCE_LIST}
)

# target_link_libraries(${project} fraction)


set_target_properties(${project} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/.bin
)