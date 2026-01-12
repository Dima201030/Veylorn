#include <iostream>
#include <cstddef>
#include <termios.h>
#include <unistd.h>

#include "world/map.h"
#include "game.h"
#include "ui/render.h"
#include "utils/conversion.h"
#include "ui/hud.h"
#include "objects/player.h"
#include "ui/renderinventory.h"
#include "objects/inventory.h"

int main() {

    Game game("", true);

    if (!game._currentMap->isLoaded()) {
        game._isRunning = false;
        return toInt(game._currentMap->getLastError());
    }

    HUD::renderHealth(game._currentMap->_player);


    std::cout << "\nKeys: ";
    if (game._inventory->_items.size() < 10) {
        std::cout << "00" << game._inventory->_items.size();
    } else if (game._inventory->_items.size() < 100) {
        std::cout << "0" << game._inventory->_items.size();
    } else {
        std::cout << game._inventory->_items.size();
    }

    std::cout << "hh";
    std::cout << "\033[?25l";

    if (game._isRunning) {
        std::cout << "\033[H";
        Render::draw(game);
        HUD::renderHealth(game._currentMap->_player);
    }

    while (game._isRunning) {

        if (game._isInInventory) {
            Render::clearScreen();
            Render::setCursorPosition(0,0);
            std::cout << "\033[H";
            RenderInventory::render(game._inventory);

            char key = getch();

            switch (key){
            case 'q':
                game._isRunning = false;
                break;
            case 'i':
                game._isInInventory = false;
                continue;
            }
            continue;
        }



        std::cout << "\033[H";
        Render::draw(game);

        char key = getch();

        if (game._currentMap->_player->_health <= 0) {
            game._isRunning = false;
            break;
        }

        switch (key) {
        case 'q':
            game._isRunning = false;
            break;
        case 'w':
            game.movePlayer(0, -1);
            break;
        case 'W':
            game.movePlayer(0, -2, true);
            break;
        case 's':
            game.movePlayer(0, 1);
            break;
        case 'S':
            game.movePlayer(0, 2, true);
            break;
        case 'd':
            game.movePlayer(1, 0);
            break;
        case 'D':
            game.movePlayer(2, 0, true);
            break;
        case 'a':
            game.movePlayer(-1, 0);
            break;
        case 'A':
            game.movePlayer(-2, 0, true);
            break;
        case 'i':
            game._isInInventory = true;
            break;
        }

        HUD::renderHealth(game._currentMap->_player);
    }

    Render::clearScreen();
    Render::setCursorPosition(0,0);
    std::cout << "\033[?25h";

    return 0;
}
