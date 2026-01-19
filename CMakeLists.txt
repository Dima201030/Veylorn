cmake_minimum_required(VERSION 3.16)

project(Veylorn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Python3_ROOT_DIR "/Library/Frameworks/Python.framework/Versions/3.12")

find_package(Python3 REQUIRED COMPONENTS Development)

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
    systems/genmaps.h
    systems/genmaps.cpp
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

    python/generatorMaps.py
    settings/settings.h settings/settings.cpp
    objects/npc.h objects/npc.cpp
)


target_include_directories(Veylorn
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Python3_INCLUDE_DIRS}
)

target_link_libraries(Veylorn PRIVATE ${Python3_LIBRARIES})
