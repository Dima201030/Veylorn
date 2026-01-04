cmake_minimum_required(VERSION 3.16)

project(Veylorn LANGUAGES CXX)

add_executable(Veylorn
    main.cpp
    lvlparser.cpp
    map.cpp
)

target_compile_features(Veylorn PRIVATE cxx_std_17)

if (MSVC)
    target_compile_options(Veylorn PRIVATE /W4)
else()
    target_compile_options(Veylorn PRIVATE -Wall -Wextra -Wpedantic)
endif()

configure_file(
    ${CMAKE_SOURCE_DIR}/examples/exampleMap.txt
    ${CMAKE_BINARY_DIR}/exampleMap.txt
    COPYONLY
)

include(GNUInstallDirs)
install(TARGETS Veylorn
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
