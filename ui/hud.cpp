#include "hud.h"

#include <iostream>

#include "../objects/player.h"
#include "utils/conversion.h"

void HUD::renderHealth(Player *player)
{
    std::cout << "\nHP: [";

    int health = toInt(player->_health);

    for (size_t i = 0; i < 10; ++i) {
        if (i < (health / 10)) {
            std::cout << "█";
        } else {
            std::cout << "░";
        }
    }

    std::cout << "] ";

    if (health < 10) {
        std::cout << "00" << health;
    } else if (health < 100) {
        std::cout << "0" << health;
    } else {
        std::cout << health;
    }

    std::cout << "/100\n";
}
