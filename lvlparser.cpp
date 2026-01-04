#include "lvlparser.h"

#include <string>
#include <fstream>
#include <filesystem>

// Checks if a file exists at the given path and is a regular file.
// Returns true if the file exists and is a regular file, false otherwise.
bool fileExists(const std::string &path) {
    return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
}

// Counts the total number of lines (rows) in the file.
// Returns the number of lines, or false (0) if the file cannot be opened.
int countColumns(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return false;
    }

    int count = 0;
    std::string line;

    while (std::getline(file, line)) {
        ++count;
    }

    file.close();

    return count;
}

// Counts the number of characters in the first line of the file.
// Used to determine the expected row width. Returns 0 if the file cannot be opened.
int countSymblsInColumn(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return false;
    }

    std::string line;

    std::getline(file, line);

    file.close();

    return line.size();
}

// Checks if all lines in the file have the same length as the first line.
// Returns true if any line has a different length, false if all lines are consistent or file cannot be opened.
bool checkSymbInCol(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return false;
    }

    std::string firstLine, line;

    getline(file, firstLine);

    int count = firstLine.size();

    while (std::getline(file, line)) {
        if (line.size() != count) {

            file.close();

            return 1;
        }
    }

    file.close();

    return 0;
}

// Checks that all lines (except the first and last) contain at least one free cell (' ').
// Returns true if the condition is met, false otherwise.
bool hasEnoughFreeCells(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return false;
    }

    std::string line;

    std::getline(file, line);

    int indexInFile = 1,
        maxIndex = countColumns(path);

    while (std::getline(file, line)) {
        if (++indexInFile >= maxIndex) {
            break;
        }

        int count = 0;
        for (char ch : line) {
            if (ch == ' ') ++count;
        }

        if (count < 1) {

            file.close();

            return false;
        }
    }

    file.close();

    return true;
}

// Checks that the first and last lines of the file are fully occupied (no free cells ' ').
// Returns true if both lines are fully occupied, false otherwise.
bool checkFirstAndLastLine(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return false;
    }

    std::string line;
    int count = 0;

    std::getline(file, line);

    for (char ch : line) {
        if (ch == ' ') {
            ++count;
        }
    }

    if (count >= 1) {

        file.close();

        return false;
    }

    int indexInFile = 1;
    int maxIndex = countColumns(path);

    while (std::getline(file, line)) {
        if (++indexInFile >= maxIndex) {
            break;
        }
    }

    count = 0;

    for (char ch : line) {
        if (ch == ' ') {
            ++count;
        }
    }

    if (count >= 1) {

        file.close();

        return false;
    }

    file.close();

    return true;
}

// Validates the map file using all checks (existence, row count, row consistency, free cells, first/last line).
// Returns ErrorsCodeMap::NOFILE if the file doesn't exist, ErrorsCodeMap::NOAVAILABLE if map is invalid, or ErrorsCodeMap::OK if valid.
ErrorsCodeMap checkToValidMap(const std::string &path) {
    if (path == "" || !fileExists(path)) {
        return ErrorsCodeMap::NOFILE;
    }

    if (countColumns(path) <= 1
        || checkSymbInCol(path)
        || !hasEnoughFreeCells(path)
        || !checkFirstAndLastLine(path)) {
        return ErrorsCodeMap::NOAVAILABLE;
    }

    return ErrorsCodeMap::OK;
}

