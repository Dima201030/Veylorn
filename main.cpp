#include <iostream>
#include <cstddef>

// #include "lvlparser.h"
#include "map.h"

int main() {
    // test, debug, DEBUG , DEBUG:
    // std::cout << countColumns("/Users/dima/PycharmProjects/HW/main.txt") << std::endl;

    // std::cout << checkToValidMap("/Users/dima/Veylorn/examples/exampleMap.txt") << std::endl;

    Map levelMap("/Users/dima/Veylorn/examples/exampleMap.txt");

    for (size_t i = 0; i < levelMap.getColumns(); ++i) {
        for (size_t j = 0; j < levelMap.getLines(); ++j) {
            std::cout << char(levelMap(i, j)) << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
