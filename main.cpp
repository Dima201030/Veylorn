#include <iostream>
#include <cstddef>
#include <termios.h>
#include <unistd.h>

#include "game.h"

#include "objects/inventory.h"
#include "objects/player.h"

#include "ui/hud.h"
#include "ui/render.h"
#include "ui/renderinventory.h"

#include "utils/conversion.h"

#include "world/map.h"

int main() {

    Game game("/Users/dima/Veylorn/maps/map3.txt", true);

    if (!game._currentMap->isLoaded()) {
        game._isRunning = false;
        return toInt(game._currentMap->getLastError());
    }

    std::cout << "\033[?25l"; // Hide cursor

    while (game._isRunning) {
        std::cout << "\033[H";

        if (game._currentMap->_player->_health <= 0) {
            game._isRunning = false;
            break;
        }

        if (game._isInInventory) {
            Render::clearScreen();
            Render::setCursorPosition(0,0);

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

        Render::draw(game);

        HUD::renderHealth(game._currentMap->_player);

        std::cout << "\nKeys: ";

        if (game._inventory->_items.size() < 10) {
            std::cout << "00" << game._inventory->_items.size();
        } else if (game._inventory->_items.size() < 100) {
            std::cout << "0" << game._inventory->_items.size();
        } else {
            std::cout << game._inventory->_items.size();
        }

        // std::cout << "\nHelp - h";

        char key = getch();

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
    }

    Render::clearScreen();
    Render::setCursorPosition(0,0);

    std::cout << "\033[?25h"; // Show cursor

    return 0;
}
