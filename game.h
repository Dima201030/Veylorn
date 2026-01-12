#pragma once

#include <string>

#include "world/map.h"

struct Inventory;

struct Game {

    Game(std::string path, bool isRunning);

    ~Game();

    Map       *_currentMap;

    Player    *_player;

    Inventory *_inventory;

    bool _isRunning = true;

    // void initNewGame();
    // void loadGame();
    // void saveGame();
    // void changeMap();

    void movePlayer(int dx, int dy, bool isRun = false);
};
