#pragma once

#include <string>
#include <cstddef>

#include "map.h"

ErrorsCodeMap checkToValidMap(const std::string &path);

size_t countColumns(const std::string &path);

size_t countSymblsInColumn(const std::string &path);
