cmake_minimum_required(VERSION 3.16)

project(Veylorn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Veylorn main.cpp
    lvlparser.h lvlparser.cpp
    examples/exampleMap.txt)

include(GNUInstallDirs)
install(TARGETS Veylorn
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
