#pragma once

#include <cstddef>

struct Map;

struct Player {
    int  _posX = 0;
    int  _posY = 0;
    int  _health = 100;

    void move(Map& map, int posX, int posY, bool isRun = false);
};
