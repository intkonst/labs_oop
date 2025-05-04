cmake_minimum_required(VERSION 3.23)

set(project "lab_2")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
    main.cc
    src/app.cc
)

set(${project}_HEADERS
    src/app.h
)

add_subdirectory(planet)
add_subdirectory(car)

set(${project}_SOURCE_LIST
    ${${project}_SOURCES}
    ${${project}_HEADERS}
)

add_executable(${project}
    ${${project}_SOURCE_LIST}
)

target_link_libraries(${project} planet car)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/db/system.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/.bin/system.txt  
    COPYONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/db/carpark.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/.bin/carpark.txt  
    COPYONLY
)

add_custom_command(
    TARGET ${project} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/db
        ${CMAKE_CURRENT_SOURCE_DIR}/.bin
    COMMENT "Copying input files..."
)

set_target_properties(${project} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/.bin
)
