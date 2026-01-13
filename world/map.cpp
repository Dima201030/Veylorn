#include <cstddef>
#include <fstream>
#include <string>
#include <iostream>

#include "map.h"
#include "lvlparser.h"
#include "../objects/object.h"
#include "../objects/player.h"

void parsePlayerFromServiceLine(const std::string &line, Player *&player) {
    std::string key;
    std::string value;

    for (size_t i = 0; i < line.size(); ++i) {
        char ch = line[i];

        if (ch == '=') {
            value.clear();
            ++i;

            while (i < line.size() && line[i] != ',') {
                value += line[i];
                ++i;
            }

            if (key == "fpx") {
                player->_posX = std::stoi(value);
            } else if (key == "fpy") {
                player->_posY = std::stoi(value);
            }
            key.clear();
        }
        else if (ch != ',') {
            key += ch;
        }
    }
}

std::string getServiceLine(std::string path) {
    std::fstream file(path);

    if (!file.is_open()) {
        return "";
    }

    std::string line;
    std::string lastNonEmpty;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            lastNonEmpty = line;
        }
    }

    return lastNonEmpty;
}

Map::Map(std::string path, Player *player) : _matrix(nullptr), _column(0), _lines(0),  _lastError(ErrorsCodeMap::OK) {

    _lastError = loadMapFile(path);

    if (_lastError != ErrorsCodeMap::OK) {
        allocateEmptyMatrix();
    } else {
        _player = player;
        _serviceLine = getServiceLine(path);
        parsePlayerFromServiceLine(_serviceLine, _player);
        parseObjects(path);
        setPlayer();
    }
}

Map::~Map() {
    for (size_t i = 0; i < _lines; ++i) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

void Map::parseObjects(std::string path)
{
    std::fstream file(path, std::ios_base::in);

    if (!file.is_open()) {
        return;
    }

    std::string line;

    for (size_t y = 0; y < _column; ++y) {
        std::getline(file, line);
        for (size_t x = 0; x < _lines; ++x) {
            switch (char(line[x])) {
            // case 'C': { // Пустой сундук
            //     Object chest(Chest{}, x, y);

            //     _objects.push_back(chest);
            //     _matrix[x][y] = CellType::CHEST;
            //     break;
            // }
            case 'g': { // Gold
                Object item(Item(ItemType::GOLD, 1), x, y);

                _objects.push_back(item);
                break;
            }
            default:
                break;
            }
        }
    }
}

bool Map::isLoaded() const {
    if (_lastError == ErrorsCodeMap::OK) {
        return true;
    } else {
        return false;
    }
}

ErrorsCodeMap Map::getLastError() const {
    return _lastError;
}

ErrorsCodeMap Map::loadMapFile(std::string path) {
    ErrorsCodeMap checkMap = checkToValidMap(path);
    if (checkMap != ErrorsCodeMap::OK) {
        return checkMap;
    }

    std::fstream file(path, std::ios_base::in);

    if (!file.is_open()) {
        return ErrorsCodeMap::NOFILE;
    }

    _column = countColumns(path) - 1;
    _lines  = countSymblsInColumn(path);

    reCreateMatrix();

    std::string line;

    for (size_t y = 0; y < _column; ++y) {
        std::getline(file, line);
        for (size_t x = 0; x < _lines; ++x) {
            switch (char(line[x])) {
            case ' ':
                _matrix[x][y] = CellType::EMPTY;
                break;
            case '#':
                _matrix[x][y] = CellType::WALL;
                break;
            case '@':
                _matrix[x][y] = CellType::PLAYER;
                break;
            case '.':
                _matrix[x][y] = CellType::TRACE;
                break;
            case 'g':
                _matrix[x][y] = CellType::GOLD;
                break;
            default:
                _matrix[x][y] = CellType::EMPTY;
                break;
            }
        }
    }

    return ErrorsCodeMap::OK;
}

void Map::allocateEmptyMatrix() {
    _column = 1;
    _lines  = 1;

    _matrix = new CellType*[_lines];
    _matrix[0] = new CellType[_column]{CellType::EMPTY};
}

void Map::reCreateMatrix() {
    if (_matrix) {
        for (size_t i = 0; i < _lines; ++i) {
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }
    _matrix = new CellType*[_lines];

    for (size_t y = 0; y < _lines; ++y) {
        _matrix[y] = new CellType[_column];
        for (size_t x = 0; x < _column; ++x) {
            _matrix[y][x] = CellType::EMPTY;
        }
    }
}

void Map::reCreateMatrix(CellType defaultValue) {
    if (_matrix) {
        for (size_t i = 0; i < _lines; ++i) {
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }
    _matrix = new CellType*[_lines];

    for (size_t y = 0; y < _lines; ++y) {
        _matrix[y] = new CellType[_column];
        for (size_t x = 0; x < _column; ++x) {
            _matrix[y][x] = defaultValue;
        }
    }
}

CellType Map::operator()(size_t column, size_t lines) {
    return _matrix[lines][column];
}

CellType Map::operator()(size_t column, size_t lines) const {
    return _matrix[lines][column];
}

CellType *Map::operator[](size_t col) {
    return _matrix[col];
}

void Map::setPlayer()
{
    _matrix[_player->_posX][_player->_posY] = CellType::PLAYER;
}

CellType *Map::operator[](size_t col) const {
    return _matrix[col];
}

size_t Map::getColumns() const{
    return _column;
}

size_t Map::getLines() const{
    return _lines;
}

CellType Map::getCell(size_t x, size_t y) const {
    return _matrix[x][y];
}

