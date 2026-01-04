#pragma once

#include <string>

#include "map.h"

// Validates the map file: checks if the file exists, all lines have equal length, there are enough free cells, and the first and last lines are fully occupied.
// Returns ErrorsCodeMap::NOFILE if the file doesn't exist, ErrorsCodeMap::NOAVAILABLE if the map is invalid, or ErrorsCodeMap::OK if valid.
ErrorsCodeMap checkToValidMap(const std::string &path);

// Counts the number of lines (rows) in the file.
// Returns the number of lines, or 0 if the file cannot be opened.
int countColumns(const std::string &path);

// Counts the number of characters in the first line of the file.
// Used to determine the width of the map. Returns 0 if the file cannot be opened.
int countSymblsInColumn(const std::string &path);
