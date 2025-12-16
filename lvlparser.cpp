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

