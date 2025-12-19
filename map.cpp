// IN TEST

#include "map.h"
#include <cstddef>

Map::Map(const char* fileName) : _column(0), _lines(0), _lastError(ErrorsCode::OK) {

    _lastError = loadMapFile(fileName);

    if (_lastError != ErrorsCode::OK) {
        allocateEmptyMatrix();
    }
}

bool Map::isLoaded() const {
    if (_lastError == ErrorsCode::OK) {
        return true;
    } else {
        return false;
    }
}

ErrorsCode Map::getLastError() const {
    return _lastError;
}

ErrorsCode Map::loadMapFile(const char* fileName) {
    return ErrorsCode::OK;
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
