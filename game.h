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

    bool _isRunning     = true;
    bool _isInInventory = false;
    bool _isInTips = false;
    bool _isInCombat = false;

    int _combatTargetX = -1;
    int _combatTargetY = -1;


    // void initNewGame();
    // void loadGame();
    // void saveGame();
    // void changeMap();

    void movePlayer(int dx, int dy, bool isRun = false);
    void attack();
};
