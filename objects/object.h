#pragma once

#include <cstddef>
#include <string>

// #include "chest.h"
#include "item.h"

struct Object {

    // Object(std::variant<Item, Chest> obj, size_t x, size_t y);

    Object(Item obj, size_t x, size_t y);

    // std::variant<Item, Chest> _object;

    Item _object;

    std::string _name;

    size_t _x, _y;
};
