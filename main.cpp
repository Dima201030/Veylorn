#include <iostream>
#include <cstddef>
#include <termios.h>
#include <unistd.h>
#include <string>
#undef slots
#include <Python.h>


#include "game.h"

#include "objects/inventory.h"
#include "objects/player.h"

#include "systems/approve.h"
#include "systems/inpusystem.h"

#include "ui/helptips.h"
#include "ui/hud.h"
#include "ui/render.h"
#include "ui/renderinventory.h"

#include "utils/conversion.h"
#include "utils/filesystem.h"

#include "world/map.h"

#define MAX_ATTEMPTS 50

void generateMap() {
    Py_Initialize();

    std::string pathCommand = "sys.path.append('" + basePath() + "')";
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(pathCommand.c_str());

    PyObject* pModule =
        PyImport_Import(PyUnicode_FromString("python.generatorMaps"));

    if (!pModule) {
        PyErr_Print();
        return;
    }

    PyObject* pFunc = PyObject_GetAttrString(pModule, "generate_map_to_file");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        PyErr_Print();
        return;
    }

    std::string mapPath = basePath() + "auxiliary/maps/map3.txt";

    PyObject* pArgs = PyTuple_New(1);
    PyTuple_SetItem(
        pArgs,
        0,
        PyUnicode_FromString(mapPath.c_str())
        );

    PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
    if (!pResult) {
        PyErr_Print();
    }


    Py_Finalize();
}

int main() {

    int countLevels = 0;

    int attempts = 0;

    Game* game = nullptr;
    std::string mapPath = basePath() + "auxiliary/maps/map3.txt";

    while (attempts < MAX_ATTEMPTS) {
        generateMap();

        delete game;
        game = new Game(mapPath, true);

        if (game->_currentMap && game->_currentMap->isLoaded()) {
            break;
        }

        attempts++;
    }

    if (!game || !game->_currentMap || !game->_currentMap->isLoaded()) {
        std::cerr << "FATAL: failed to generate valid map\n";
        std::abort();
    }

    std::cout << "\033[?25l"; // Hide cursor

    renderTips();

    while (game->_isRunning) {
        std::cout << "\033[H";

        if (game->_currentMap->_player->_health <= 0) {
            game->_isRunning = false;
            break;
        }

        if (countLevels == 1) {
            game->_isRunning = false;
            continue;
        }
        if (game->_currentMap->isEmptyMobs()) {
            std::cout << "Все мобы уничтожены! Генерируем новый уровень...\n";

            delete game;

            int attempts = 0;
            while (attempts < MAX_ATTEMPTS) {
                generateMap();
                game = new Game(mapPath, true);

                if (game->_currentMap && game->_currentMap->isLoaded()) {
                    break;
                }

                delete game;
                game = nullptr;
                attempts++;
            }

            if (!game || !game->_currentMap || !game->_currentMap->isLoaded()) {
                std::cerr << "FATAL: failed to generate valid map\n";
                std::abort();
            }

            countLevels++;
            continue;
        }

        if (game->_isInInventory) {
            Render::clearScreen();
            Render::setCursorPosition(0,0);

            RenderInventory::render(game->_inventory);

            char key = getch();

            switch (key){
            case 'q':
                if (approveWindow()) {
                    game->_isRunning = false;
                }
                break;
            case 'i':
                game->_isInInventory = false;
                continue;
            }
            continue;
        }

        if (game->_isInTips) {
            Render::clearScreen();
            Render::setCursorPosition(0,0);

            renderTips();

            char key = getch();

            switch (key){
            case 'q':
                if (approveWindow()) {
                    game->_isRunning = false;
                }
                break;
            case 'h':
                game->_isInTips = false;
                continue;
            }
            continue;
        }

        Render::draw(*(game));

        HUD::renderHealth(game->_currentMap->_player);

        std::cout << "\nKeys: ";

        if (game->_inventory->_items.size() < 10) {
            std::cout << "00" << game->_inventory->_items.size();
        } else if (game->_inventory->_items.size() < 100) {
            std::cout << "0" << game->_inventory->_items.size();
        } else {
            std::cout << game->_inventory->_items.size();
        }

        std::cout << "\nHelp - h";

        char ch = 0;
        Key key = getKey(ch);

        switch (key) {
        case Key::Up:
            game->movePlayer(0, -1);
            break;
        case Key::Down:
            game->movePlayer(0, 1);
            break;
        case Key::Left:
            game->movePlayer(-1, 0);
            break;
        case Key::Right:
            game->movePlayer(1, 0);
            break;
        case Key::Char:
            switch (ch) {
            case 'q':
                if (approveWindow()) {
                    game->_isRunning = false;
                }
                break;
            case 'w':
                game->movePlayer(0, -1);
                break;
            case 'W':
                game->movePlayer(0, -2, true);
                break;
            case 's':
                game->movePlayer(0, 1);
                break;
            case 'S':
                game->movePlayer(0, 2, true);
                break;
            case 'd':
                game->movePlayer(1, 0);
                break;
            case 'D':
                game->movePlayer(2, 0, true);
                break;
            case 'a':
                game->movePlayer(-1, 0);
                break;
            case 'A':
                game->movePlayer(-2, 0, true);
                break;
            case 'i':
                game->_isInInventory = true;
                break;
            case 'f':
                if (game->_isInCombat) {
                    game->attack();
                }
                break;
            case 'h':
                game->_isInTips = true;
                break;
            case '/':
                game->_isInTips = true;
                break;
            }
            break;
        default:
            break;
        }
    }

    Render::clearScreen();
    Render::setCursorPosition(0,0);

    std::cout << "\033[?25h"; // Show cursor

    std::cout << "Thanks for your time" << std::endl;

    return 0;
}
