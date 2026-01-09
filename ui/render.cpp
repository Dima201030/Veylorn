#include "render.h"

#include <iostream>

#include "../game.h"
#include "../world/map.h"

char Render::cellToChar(CellType cell) {
    switch (cell) {
    case CellType::EMPTY:
        return ' ';
    case CellType::WALL:
        return '#';
    case CellType::PLAYER:
        return '@';
    case CellType::TRACE:
        return '.';
    case CellType::CHEST:
        return 'c';
    case CellType::GOLD:
        return 'g';
    default:
        return '?';
    }
}

void Render::clearScreen() {
    std::cout << "\033[2J";
}

void Render::setCursorPosition(int x, int y) {
    std::cout << "\033[" << y + 1 << ";" << (x * 2) + 1 << "H";
}

void Render::applyColor(CellType cell) {
    switch (cell) {
    case CellType::WALL:
        // std::cout << "\033[90m";  // Серый
        std::cout << "\033[33m";  // Желтый
        break;
    case CellType::PLAYER:
        std::cout << "\033[92m";  // Зеленый
        break;
    case CellType::TRACE:
        std::cout << "\033[37m";  // Белый
        break;
    case CellType::GOLD:
        std::cout << "\033[32m";  // Желтый
        break;
    default:
        std::cout << "\033[0m";   // Сброс
    }
}

void Render::resetColor() {
    std::cout << "\033[0m";
}

void Render::drawCell(CellType cell) {
    applyColor(cell);
    std::cout << cellToChar(cell);
    resetColor();
    std::cout << ' ';
}

void Render::draw(const Game& game) {
    const Map& map = *game._currentMap;


    for (size_t y = 0; y < map.getLines(); ++y) {
        for (size_t x = 0; x < map.getColumns(); ++x) {
            setCursorPosition((int)y, (int)x);
            drawCell(map(x, y));
        }
    }
    std::cout << std::flush;
}
