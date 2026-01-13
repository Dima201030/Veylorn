cmake_minimum_required(VERSION 3.16)

project(Veylorn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Veylorn
    main.cpp

    game.h
    game.cpp

    world/lvlparser.h
    world/lvlparser.cpp
    world/map.h
    world/map.cpp

    # objects/chest.h
    # objects/chest.cpp
    objects/inventory.h
    objects/inventory.cpp
    objects/item.h
    objects/object.h
    objects/object.cpp
    objects/player.h
    objects/player.cpp

    systems/approve.h
    systems/approve.cpp
    systems/inpusystem.h
    systems/inpuSystem.cpp

    ui/helptips.h
    ui/helptips.cpp
    ui/hud.h
    ui/hud.cpp
    ui/render.h
    ui/render.cpp
    ui/renderinventory.h
    ui/renderinventory.cpp

    utils/conversion.h
    utils/conversion.cpp
    utils/filesystem.h
    utils/filesystem.cpp

    auxiliary/maps/map1.txt
    auxiliary/maps/map2.txt
    auxiliary/maps/map3.txt
    auxiliary/help.txt

)

target_include_directories(Veylorn
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
