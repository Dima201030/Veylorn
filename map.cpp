#include <cstddef>
#include <fstream>
#include <string>

#include "map.h"
#include "lvlparser.h"

Map::Map(const char* path) : _column(0), _lines(0), _matrix(nullptr), _lastError(ErrorsCodeMap::OK) {

    _lastError = loadMapFile(path);

    if (_lastError != ErrorsCodeMap::OK) {
        allocateEmptyMatrix();
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

ErrorsCodeMap Map::loadMapFile(const char* path) {
    ErrorsCodeMap checkMap = checkToValidMap(path);
    if (checkMap != ErrorsCodeMap::OK) {
        return checkMap;
    }

    std::fstream file(path, std::ios_base::in);

    if (!file.is_open()) {
        return ErrorsCodeMap::NOFILE;
    }

    _column = countColumns(path);
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

int Map::operator()(int column, int lines) {
    return _matrix[lines][column];
}

const int Map::operator()(int column, int lines) const {
    return _matrix[lines][column];
}

int* Map::operator[](int col) {
    return _matrix[col];
}

const int* Map::operator[](int col) const {
    return _matrix[col];
}

int Map::getColumns() const{
    return _column;
}

int Map::getLines() const{
    return _lines;
}


