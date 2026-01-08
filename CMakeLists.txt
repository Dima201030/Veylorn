cmake_minimum_required(VERSION 3.16)
project(Veylorn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Veylorn
    main.cpp
    map.cpp
    lvlparser.cpp
    map.h
    lvlparser.h
    player.h
    object.h
)

target_include_directories(Veylorn PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (MSVC)
    target_compile_options(Veylorn PRIVATE /W4 /permissive-)
else()
    target_compile_options(Veylorn PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/maps)

configure_file(
    ${CMAKE_SOURCE_DIR}/map1.txt
    ${CMAKE_BINARY_DIR}/map1.txt
    COPYONLY
)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/maps)

file(GLOB MAP_FILES
    "${CMAKE_SOURCE_DIR}/map*.txt"
    "${CMAKE_SOURCE_DIR}/maps/*.txt"
)

foreach(MAP_FILE ${MAP_FILES})
    get_filename_component(MAP_NAME ${MAP_FILE} NAME)
    configure_file(${MAP_FILE} ${CMAKE_BINARY_DIR}/maps/${MAP_NAME} COPYONLY)
endforeach()
