#include <cstddef>
#include <fstream>
#include <string>

#include "map.h"
#include "lvlparser.h"

void parsePlayerFromServiceLine(const std::string& line, Player& player) {
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
                player.posX = std::stoi(value);
            } else if (key == "fpy") {
                player.posY = std::stoi(value);
            } else if (key == "s") {
                player.ch = value[0];
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

Map::Map(std::string path) : _matrix(nullptr), _column(0), _lines(0),  _lastError(ErrorsCodeMap::OK) {

    _lastError = loadMapFile(path);

    if (_lastError != ErrorsCodeMap::OK) {
        allocateEmptyMatrix();
    } else {
        _serviceLine = getServiceLine(path);
        parsePlayerFromServiceLine(_serviceLine, _player);
        setPlayer();
    }
}

Map::~Map() {
    for (size_t i = 0; i < _lines; ++i) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
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

    recreateMatrix();

    std::string line;

    for (size_t y = 0; y < _column; ++y) {
        std::getline(file, line);
        for (size_t x = 0; x < _lines; ++x) {
            _matrix[x][y] = line[x];
        }
    }

    return ErrorsCodeMap::OK;
}

void Map::allocateEmptyMatrix() {
    _column = 1;
    _lines  = 1;

    _matrix = new int*[_lines];
    _matrix[0] = new int[_column]{0};
}

void Map::recreateMatrix() {
    if (_matrix) {
        for (size_t i = 0; i < _lines; ++i) {
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }
    _matrix = new int*[_lines];

    for (size_t y = 0; y < _lines; ++y) {
        _matrix[y] = new int[_column];
        for (size_t x = 0; x < _column; ++x) {
            _matrix[y][x] = 0;
        }
    }
}

void Map::recreateMatrix(int defaultValue) {
    if (_matrix) {
        for (size_t i = 0; i < _lines; ++i) {
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }
    _matrix = new int*[_lines];

    for (size_t y = 0; y < _lines; ++y) {
        _matrix[y] = new int[_column];
        for (size_t x = 0; x < _column; ++x) {
            _matrix[y][x] = defaultValue;
        }
    }
}

int Map::operator()(size_t column, size_t lines) {
    return _matrix[lines][column];
}

int Map::operator()(size_t column, size_t lines) const {
    return _matrix[lines][column];
}

int* Map::operator[](size_t col) {
    return _matrix[col];
}

void Map::movePlayer(int posX, int posY)
{
    if (_matrix[_player.posX + posX][_player.posY + posY] != '#') {
        _errorFlag = "·";
        if (_matrix[_player.posX + posX][_player.posY + posY] == 'E') {
            _errorFlag = "✅";
        }
        clearPlayer();
        _player.posX += posX;
        _player.posY += posY;
        setPlayer();
    } else {
        _errorFlag = "🛑";
    }

}

void Map::setPlayer()
{
    _matrix[_player.posX][_player.posY] = _player.ch;
}

void Map::clearPlayer()
{
    _matrix[_player.posX][_player.posY] = '.';
}

const int* Map::operator[](size_t col) const {
    return _matrix[col];
}

size_t Map::getColumns() const{
    return _column;
}

size_t Map::getLines() const{
    return _lines;
}
