#include "helptips.h"

#include <fstream>
#include <string>
#include <iostream>

#include "utils/filesystem.h"

void renderTips() {
    std::fstream file(basePath() + "auxiliary/help.txt");

    if (!file.is_open()) {
        return;
    }

    std::string line;

    while(std::getline(file, line)) {
        std::cout << line << "\n";
    }

    file.close();
}
