#pragma once

#include <cstddef>

#include "chest.h"
#include "item.h"

struct Object {

    Object(std::variant<Item, Chest> obj, size_t x, size_t y) : object(std::move(obj)), _x(x), _y(y) {}

    std::variant<Item, Chest> object;
    size_t _x, _y;
};
