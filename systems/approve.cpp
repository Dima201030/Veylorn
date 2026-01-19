#include "approve.h"
#include <iostream>
#include "inpusystem.h"
#include "ui/render.h"

bool approveWindow(bool isPushDone) {
    bool isEnter = false;

    while (!isEnter) {
        Render::clearScreen();
        Render::setCursorPosition(0, 0);

        std::cout << "╔══════════════ INVENTORY ══════════════╗\n";
        std::cout << "║                                       ║\n";

        if (isPushDone) {
            std::cout << "║                \033[47;30m Done \033[0m                 ║\n";
            std::cout << "║                Decline                ║\n";
        } else {
            std::cout << "║                 Done                  ║\n";
            std::cout << "║               \033[47;30m Decline \033[0m               ║\n";
        }

        std::cout << "║                                       ║\n";
        std::cout << "╚═══════════════════════════════════════╝\n";

        char ch = 0;
        Key key = getKey(ch);

        switch (key) {
        case Key::Down:
        case Key::Up:
            isPushDone = !isPushDone;
            break;
        case Key::Enter:
            isEnter = true;
            break;
        default:
            break;
        }
    }

    return isPushDone;
}
