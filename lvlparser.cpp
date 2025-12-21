#include "lvlparser.h"

#include <string>
#include <fstream>
#include <filesystem>

bool fileExists(const std::string &path) {
    return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
}

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

    return count;
}

bool checkSymbInCol(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    std::string firstLine;
    getline(file, firstLine);

    int count = firstLine.size();

    std::string line;

    while (std::getline(file, line)) {
        if (line.size() != count) {
            return 1;
        }
    }

    return 0;
}

bool hasEnoughFreeCells(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    std::string line;

    std::getline(file, line);

    int indexInFile = 1;
    int maxIndex = countColumns(path);

    while (std::getline(file, line)) {
        if (++indexInFile >= maxIndex) {
            break;
        }

        int count = 0;
        for (char ch : line) {
            if (ch == ' ') ++count;
        }

        if (count < 1) {
            return false;
        }
    }

    return true;
}

bool checkFirstAndLastLine(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    std::string line;

    std::getline(file, line);

    int count = 0;

    for (char ch : line) {
        if (ch == ' ') ++count;
        }

    if (count >= 1) {
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
        if (ch == ' ') ++count;
        }

    if (count >= 1) {
        return false;
    }

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

