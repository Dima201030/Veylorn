#pragma once

enum class Key {
    None,
    Up,
    Down,
    Left,
    Right,
    HELP,
    INVENTORY,
    Char
};

Key getKey(char& outChar);
char getch();
