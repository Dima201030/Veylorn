#include "game.h"
#include "objects/player.h"

Game::~Game()
{
    delete _currentMap;
}

void Game::movePlayer(int dx, int dy, bool isRun)
{
    if(_currentMap){
        _currentMap->_player->move(*(_currentMap), dx, dy, isRun);
    }
}
