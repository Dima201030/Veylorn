#include <iostream>
#include <cstddef>
#include <termios.h>
#include <unistd.h>

#include "world/map.h"
#include "game.h"
#include "ui/render.h"
#include "utils/conversion.h"

// char getch()
// {
//     termios oldt, newt;
//     tcgetattr(STDIN_FILENO, &oldt);

//     newt = oldt;
//     newt.c_lflag &= ~(ICANON | ECHO);

//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);

//     char ch = static_cast<char>(getchar());

//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//     return ch;
// }

// int main(int argc, char** argv) {
    // system("clear");
    // std::string mapName = "/Users/dima/Veylorn/map3.txt";
    // if (argc == 2) {
    //     mapName = argv[1];
    //     std::cout << argv[1];
    // }
    // std::cout << "\033[?25l";
    // Map levelMap(mapName);

    // if (!levelMap.isLoaded()) {
    //     return 1;
    // }
    // while (true) {
    //     std::cout << "\033[H";

    //     for (size_t i = 0; i < levelMap.getColumns(); ++i) {
    //         for (size_t j = 0; j < levelMap.getLines(); ++j) {
    //             std::cout << renderCell(levelMap(i, j)) << ' ';
    //         }
    //         std::cout << '\n';
    //     }

    //     std::cout << "\n";
    //     std::cout << levelMap._errorFlag << ' ';

    //     std::cout << "\nHP: [";

    //     int health = static_cast<int>(levelMap._player._health);
    //     int healthBars = health / 10;

    //     for (int i = 0; i < 10; ++i) {
    //         if (i < healthBars) {
    //             std::cout << "█";
    //         } else {
    //             std::cout << "░";
    //         }
    //     }

    //     std::cout << "] ";

    //     if (health < 10) {
    //         std::cout << "00" << health;
    //     } else if (health < 100) {
    //         std::cout << "0" << health;
    //     } else {
    //         std::cout << health;
    //     }

    //     std::cout << "/100\n";

    //     char key = getch();

    //     switch (key) {
    //     case 'w':
    //         levelMap._player.move(levelMap, 0, -1);
    //         break;
    //     case 'W':
    //         levelMap._player.move(levelMap, 0, -2, true);
    //         break;
    //     case 's':
    //         levelMap._player.move(levelMap, 0, 1);
    //         break;
    //     case 'S':
    //         levelMap._player.move(levelMap, 0, 2, true);
    //         break;
    //     case 'd':
    //         levelMap._player.move(levelMap, 1, 0);
    //         break;
    //     case 'D':
    //         levelMap._player.move(levelMap, 2, 0, true);
    //         break;
    //     case 'a':
    //         levelMap._player.move(levelMap, -1, 0);
    //         break;
    //     case 'A':
    //         levelMap._player.move(levelMap, -2, 0, true);
    //         break;
    //     case 'l':
    //         levelMap._player._health -= 10;
    //         if (levelMap._player._health < 0) levelMap._player._health = 0;
    //         break;
    //     default:
    //         break;
    //     }

    //     std::cout << std::flush;
    // }
// }

int main() {

    Game game;
    game._currentMap = new Map("/Users/dima/Veylorn/maps/map3.txt");

    if (!game._currentMap->isLoaded()) {
        game.isRunning = false;
        std::cout << toInt(game._currentMap->getLastError()) << std::endl;
        return 1;
    }

    game.isRunning = true;
    std::cout << "hh";
    // std::cout
    std::cout << "\033[?25l";


    while (game.isRunning) {
        // std::cout << "\033[H";
        Render::draw(game);

        char key = getch();

        if (key == 'q' || key == 'Q') {
            game.isRunning = false;
        }

        switch (key) {
        case 'w':
            game.movePlayer(0, -1); break;
        case 'W':
            game.movePlayer(0, -2, true); break;
        case 's':
            game.movePlayer(0, 1); break;
        case 'S':
            game.movePlayer(0, 2, true); break;
        case 'd':
            game.movePlayer(1, 0); break;
        case 'D':
            game.movePlayer(2, 0, true); break;
        case 'a':
            game.movePlayer(-1, 0); break;
        case 'A':
            game.movePlayer(-2, 0, true); break;

        }
    }

    Render::clearScreen();
    Render::setCursorPosition(0,0);
    std::cout << "\033[?25h";

    return 0;
}
