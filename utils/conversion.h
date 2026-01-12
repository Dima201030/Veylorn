#pragma once

#include <string>
#include <cstddef>
#include <termios.h>
#include <unistd.h>

#include "../world/map.h"

// ErrorsCodeMap
std::string toString(ErrorsCodeMap err);
int         toInt   (ErrorsCodeMap err);

// size_t and int
int         toInt(size_t value);
size_t      toST (int value   );

// char
char getch();

