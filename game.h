#pragma once

// #include <vector>

#include "world/map.h"

struct Game {
    Map* _currentMap;
    ~Game();

    bool isRunning;

    void initNewGame();
    void loadGame();
    void saveGame();
    void changeMap();

    void movePlayer(int dx, int dy, bool isRun = false);
};
