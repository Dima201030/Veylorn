#include "map.h"
#include <cstddef>

#include "lvlparser.h"

Map::Map(const char* path) : _column(0), _lines(0), _matrix(nullptr), _lastError(ErrorsCodeMap::OK) {

    _lastError = loadMapFile(path);

    if (_lastError != ErrorsCodeMap::OK) {
        allocateEmptyMatrix();
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

ErrorsCodeMap Map::loadMapFile(const char* path) {
    ErrorsCodeMap checkMap = checkToValidMap(path);
    if (checkMap != ErrorsCodeMap::OK) {
        return checkMap;
    }

    // In dev...

    return ErrorsCodeMap::OK;
}

void Map::allocateEmptyMatrix() {
    _column = 1;
    _lines  = 1;

    _matrix = new int*[_lines];
    _matrix[0] = new int[_column]{0};
}

int Map::operator()(int col, int line) {
    return _matrix[col][line];
}

const int Map::operator()(int col, int line) const {
    return _matrix[col][line];
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

bool Map::isCheckMapLevl() {
    return true;
}
