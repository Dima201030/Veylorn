#include <string>
#include <fstream>
#include <filesystem>
#include <cstddef>
#include <filesystem>

#include "lvlparser.h"

bool fileExists(const std::string &path) {
    return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
}

size_t countColumns(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return false;
    }

    size_t count = 0;
    std::string line;

    while (std::getline(file, line)) {
        ++count;
    }

    file.close();

    return count;
}

size_t countSymblsInColumn(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return false;
    }

    std::string line;

    std::getline(file, line);

    file.close();

    return line.size();
}

bool checkSymbInCol(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return false;
    }

    std::string firstLine, line;

    getline(file, firstLine);

    size_t count = firstLine.size();
    size_t columns = countColumns(path);
    size_t i = 0;

    while (std::getline(file, line)) {
        if (line.size() != count && i != columns - 2) {

            file.close();

            return 1;
        }
        ++i;
    }

    file.close();

    return 0;
}

bool hasEnoughFreeCells(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return false;
    }

    std::string line;

    std::getline(file, line);

    size_t indexInFile = 1,
           maxIndex = countColumns(path) - 1;

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

    size_t indexInFile = 1;
    size_t maxIndex = countColumns(path) - 1;

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

