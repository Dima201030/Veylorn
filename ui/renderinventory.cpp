#include "renderinventory.h"

#include <iostream>
#include <iomanip>

#include "../objects/inventory.h"
#include "../objects/object.h"

void RenderInventory::render(Inventory* inventory) {
    if (!inventory) {
        std::cout << "[Inventory] error: inventory is null\n";
        return;
    }

    const std::vector<Object> items = inventory->_items;

    std::cout << "\n";
    std::cout << "╔══════════════ INVENTORY ══════════════╗\n";

    if (items.empty()) {
        std::cout << "║               ( empty )               ║\n";
    } else {
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << "║ " << std::setw(2) << i + 1 << ". " << std::left << std::setw(33) << items[i]._name << " ║\n";
        }
    }

    std::cout << "╚═══════════════════════════════════════╝\n";
}
