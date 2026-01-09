#include "player.h"

#include "world/map.h"
#include "utils/conversion.h"

void Player::move(Map& map, int posX, int posY, bool isRun) {

    int newX = this->_posX + posX;

    if (newX < 0 || newX >= toInt(map.getLines())) {
        if (isRun && (posX == 2 || posX == -2)) {
            move(map, posX / 2, 0, false);
        } else {
            map._errorFlag = "🛑";
        }
        return;
    }

    int newY = this->_posY + posY;

    if (newY < 0 || newY >= toInt(map.getColumns())) {
        if (isRun && (posY == 2 || posY == -2)) {
            move(map, 0, posY / 2, false);
        } else {
            map._errorFlag = "🛑";
        }
        return;
    }


    if (isRun) {
        if (posX == 2) {
            if (map[toST(this->_posX + 2)][this->_posY] != CellType::WALL) {
                if (map[toST(this->_posX + 1)][this->_posY] != CellType::WALL) {
                    map._errorFlag = "·";
                    map[toST(this->_posX)][this->_posY] = CellType::TRACE;
                    this->_posX += 2;
                    map[toST(this->_posX - 1)][this->_posY] = CellType::TRACE;
                    map.setPlayer();
                } else {
                    map._errorFlag = "🛑";
                }
            } else {
                move(map, posX - 1, posY, false);
            }
        }
        else if (posX == -2) {
            if (map[toST(this->_posX - 2)][this->_posY] != CellType::WALL) {
                if (map[toST(this->_posX - 1)][this->_posY] != CellType::WALL) {
                    map._errorFlag = "·";
                    map[toST(this->_posX)][this->_posY] = CellType::TRACE;
                    this->_posX -= 2;
                    map[toST(this->_posX + 1)][this->_posY] = CellType::TRACE;
                    map.setPlayer();
                } else {
                    map._errorFlag = "🛑";
                }
            } else {
                move(map, posX + 1, posY, false);
            }
        }

        if (posY == 2) {
            if (map[toST(this->_posX)][this->_posY + 2] != CellType::WALL) {
                if (map[toST(this->_posX)][this->_posY + 1] != CellType::WALL) {
                    map._errorFlag = "·";
                    map[toST(this->_posX)][this->_posY] = CellType::TRACE;
                    this->_posY += 2;
                    map[toST(this->_posX)][this->_posY - 1] = CellType::TRACE;
                    map.setPlayer();
                } else {
                    map._errorFlag = "🛑";
                }
            } else {
                move(map, posX, posY - 1, false);
            }
        }
        else if (posY == -2) {
            if (map[toST(this->_posX)][this->_posY - 2] != CellType::WALL) {
                if (map[toST(this->_posX)][this->_posY - 1] != CellType::WALL) {
                    map._errorFlag = "·";
                    map[toST(this->_posX)][this->_posY] = CellType::TRACE;
                    this->_posY -= 2;
                    map[toST(this->_posX)][this->_posY + 1] = CellType::TRACE;
                    map.setPlayer();
                } else {
                    map._errorFlag = "🛑";
                }
            } else {
                move(map, posX, posY + 1, false);
            }
        }
    }
    else {
        if (map[toST(this->_posX + posX)][this->_posY + posY] != CellType::WALL) {
            map._errorFlag = "·";
            map[toST(this->_posX)][this->_posY] = CellType::TRACE;
            this->_posX += posX;
            this->_posY += posY;
            map.setPlayer();
        } else {
            map._errorFlag = "🛑";
        }
    }
}
