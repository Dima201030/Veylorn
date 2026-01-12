cmake_minimum_required(VERSION 3.16)

project(Veylorn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Veylorn
    main.cpp

    game.h
    game.cpp

    world/map.h
    world/map.cpp
    world/lvlparser.h
    world/lvlparser.cpp

    objects/object.h
    objects/player.h
    objects/player.cpp
    objects/chest.h
    objects/chest.cpp
    objects/item.h
    objects/item.cpp
    objects/inventory.h
    objects/inventory.cpp

    ui/render.h
    ui/render.cpp

    maps/map1.txt
    maps/map2.txt
    maps/map3.txt
    utils/conversion.h utils/conversion.cpp
    ui/hud.h ui/hud.cpp
    ui/renderinventory.h ui/renderinventory.cpp
    objects/object.cpp

)

target_include_directories(Veylorn
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
