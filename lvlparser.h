#pragma once

#include <string>

#include "map.h"

ErrorsCodeMap checkToValidMap(const std::string &path);
int countColumns(const std::string &path);
int countSymblsInColumn(const std::string &path);
