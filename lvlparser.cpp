#include "lvlparser.h"

#include <string>
#include <fstream>

int countColumns(const std::string &path) {
    if (path == "") {
        return 0;
    }

    std::ifstream file(path);

    int count = 0;

    std::string line;

    while (std::getline(file, line)) {
        ++count;
    }

    return count;
}

bool checkSymbInCol(const std::string &path) {
    if (path == "") {
        return 0;
    }

    std::ifstream file(path);

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

int checkToValidMap(const std::string &path) {
    if (path == "") {
        return 1;
    }

    if (countColumns(path) <= 1) {
        return 2;
    }

    if (checkSymbInCol(path)) {
        return 3;
    }

    return 0;
}

