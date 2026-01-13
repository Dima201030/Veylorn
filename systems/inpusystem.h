#pragma once

enum class Key {
    None,
    Up,
    Down,
    Left,
    Right,
    HELP,
    INVENTORY,
    Enter,
    Char
};

Key getKey(char& outChar);
char getch();
