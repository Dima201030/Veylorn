#include "inpusystem.h"
#include <termios.h>
#include <unistd.h>
#include <cstdio>

char InputSystem::getKey() {
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch = static_cast<char>(getchar());

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
