#include <iostream>
#include <cstddef>

#include "map.h"

int main() {

    Map levelMap("/Users/dima/Veylorn/examples/exampleMap.txt");

    for (size_t i = 0; i < levelMap.getColumns(); ++i) {
        for (size_t j = 0; j < levelMap.getLines(); ++j) {
            std::cout << char(levelMap(i, j)) << ' ';
        }

        std::cout << '\n';
    }

    return 0;
}
