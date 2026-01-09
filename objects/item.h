#pragma once

#include <cstddef>

enum class ItemType : int{
    NONE = 0,
    GOLD
};

struct Item {

    explicit Item(ItemType type, size_t amount): _type(type), _amount(amount) {}

    ItemType _type = ItemType::NONE;

    size_t _amount = 1;
};

