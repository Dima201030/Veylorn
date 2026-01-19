#include "inpusystem.h"
#include <termios.h>
#include <unistd.h>
#include <cstdio>

Key getKey(char& outChar) {
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char c = getchar();

    if (c == '\x1b') {
        char seq1 = getchar();
        char seq2 = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        if (seq1 == '[') {
            switch (seq2) {
            case 'A': return Key::Up;
            case 'B': return Key::Down;
            case 'C': return Key::Right;
            case 'D': return Key::Left;
            }
        }
        return Key::None;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    if (c == '\n') {
        return Key::Enter;
    }

    outChar = c;
    return Key::Char;
}

char getch() {
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch = static_cast<char>(getchar());

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
