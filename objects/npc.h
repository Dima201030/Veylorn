#pragma once

#include <cstddef>

struct NPC {
    size_t x;
    size_t y;

    int health = 20;
    int damage = 5;
};
