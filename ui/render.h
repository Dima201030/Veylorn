#pragma once

#include "../world/map.h"
#include "../game.h"

struct Render {
    static void draw(const Game& game);
    static void clearScreen();
    static void setCursorPosition(int x, int y);

private:
    static char cellToChar(CellType cell);
    static void drawCell(CellType cell);
    static void applyColor(CellType cell);
    static void resetColor();
};
