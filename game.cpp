#include "game.h"
#include "objects/player.h"
#include "world/map.h"
#include "objects/inventory.h"
#include "objects/object.h"
#include <objects/item.h>

Game::Game(std::string path, bool isRunning) : _isRunning(isRunning){
    _player = new Player();
    _currentMap = new Map(path, _player);

    if (!_currentMap->isLoaded()) {
        _isRunning = false;
    }

    _inventory = new Inventory(_player);
}

Game::~Game() {
    delete _inventory;
    delete _player;
    delete _currentMap;
}

void Game::movePlayer(int dx, int dy, bool isRun) {
    if (*(_currentMap[dy][dx]) == CellType::GOLD) {
        _inventory->_items.push_back(Object(Item(ItemType::GOLD, 1), dx, dy));
    }

    if(_currentMap){
        _currentMap->_player->move(*(_currentMap), dx, dy, isRun);
    }
}
