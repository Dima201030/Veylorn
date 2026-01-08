#include <iostream>
#include <cstddef>
#include <termios.h>
#include <unistd.h>

#include "map.h"

char getch()
{
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch = static_cast<char>(getchar());

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}


int main(int argc, char** argv) {
    system("clear");
    std::string mapName = "/Users/dima/Veylorn/map1.txt";
    if (argc == 2) {
        mapName = argv[1];
        std::cout << argv[1];
    }
    std::cout << "\033[?25l";
    Map levelMap(mapName);

    if (!levelMap.isLoaded()) {
        return 1;
    }
    while (true) {
        std::cout << "\033[H";

        for (size_t i = 0; i < levelMap.getColumns(); ++i) {
            for (size_t j = 0; j < levelMap.getLines(); ++j) {
                std::cout << char(levelMap(i, j)) << ' ';
            }
            std::cout << '\n';
        }
        std::cout << levelMap._errorFlag << std::endl;


        char key = getch();

        switch (key) {
        case 'w':
            levelMap.movePlayer(0, -1);
            break;
        case 'W':
            levelMap.movePlayer(0, -2, true);
            break;
        case 's':
            levelMap.movePlayer(0, 1);
            break;
        case 'S':
            levelMap.movePlayer(0, 2, true);
            break;
        case 'd':
            levelMap.movePlayer(1, 0);
            break;
        case 'D':
            levelMap.movePlayer(2, 0, true);
            break;
        case 'a':
            levelMap.movePlayer(-1, 0);
            break;
        case 'A':
            levelMap.movePlayer(-2, 0, true);
            break;

        default:
            break;
        }

        std::cout << std::flush;
    }
}
