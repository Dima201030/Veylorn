#pragma once

#include <vector>

#include "object.h"

struct Player;

struct Inventory {

    Inventory(Player *player);

    Player *_player;

    std::vector<Object> _items;
};
