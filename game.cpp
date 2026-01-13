#include "game.h"


#include "objects/player.h"
#include "world/map.h"
#include "objects/inventory.h"
#include <objects/item.h>
#include "utils/conversion.h"

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

    int newX = _player->_posX + dx;

    if (newX <= 0 || newX >= toInt(_currentMap->getLines())) {
        return;
    }

    int newY = _player->_posY + dy;

    if (newY <= 0 || newY >= toInt(_currentMap->getColumns())) {
        return;
    }

    size_t x = toST(_player->_posX + dx);
    size_t y = toST(_player->_posY + dy);

    if (isRun) {
        if (dx != 0) {
            if (_currentMap->getCell(x - 1, y) == CellType::GOLD) {
                _inventory->_items.emplace_back(Item(ItemType::GOLD, 100), x, y);
            }

        } else {
            if (_currentMap->getCell(x, y - 1) == CellType::GOLD) {
                _inventory->_items.emplace_back(Item(ItemType::GOLD, 100), x, y);
            }
        }
    }

    if (_currentMap->getCell(x, y) == CellType::GOLD) {
        _inventory->_items.emplace_back(Item(ItemType::GOLD, 100), x, y);
    }

    if(_currentMap){
        _currentMap->_player->move(*(_currentMap), dx, dy, isRun);
    }
}
