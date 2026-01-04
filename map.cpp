#include <cstddef>
#include <fstream>
#include <string>

#include "map.h"
#include "lvlparser.h"

// Constructor: loads the map from the given file path. If loading fails, allocates a default empty matrix.
Map::Map(const char* path) : _column(0), _lines(0), _matrix(nullptr), _lastError(ErrorsCodeMap::OK) {

    _lastError = loadMapFile(path);

    if (_lastError != ErrorsCodeMap::OK) {
        allocateEmptyMatrix();
    }
}

// Destructor: frees all allocated memory for the matrix.
Map::~Map() {
    for (size_t i = 0; i < _lines; ++i) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

// Returns true if the map was successfully loaded, false otherwise.
bool Map::isLoaded() const {
    if (_lastError == ErrorsCodeMap::OK) {
        return true;
    } else {
        return false;
    }
}

// Returns the last error code that occurred in the map.
ErrorsCodeMap Map::getLastError() const {
    return _lastError;
}

// Loads the map from a file and fills the internal matrix. Performs validation before loading.
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

// Allocates a default 1x1 matrix with a zero value.
void Map::allocateEmptyMatrix() {
    _column = 1;
    _lines  = 1;

    _matrix = new int*[_lines];
    _matrix[0] = new int[_column]{0};
}

// Recreates the matrix with current dimensions and initializes all cells to zero.
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

// Recreates the matrix with current dimensions and initializes all cells to the specified default value.
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

// Provides access to a specific cell (column, line). Allows read/write.
int Map::operator()(int column, int lines) {
    return _matrix[lines][column];
}

// Provides read-only access to a specific cell (column, line).
const int Map::operator()(int column, int lines) const {
    return _matrix[lines][column];
}

// Returns a pointer to the column, allowing access to the whole column.
int* Map::operator[](int col) {
    return _matrix[col];
}

// Returns a const pointer to the column for read-only access.
const int* Map::operator[](int col) const {
    return _matrix[col];
}

// Returns the number of columns (vertical size).
int Map::getColumns() const{
    return _column;
}

// Returns the number of lines (horizontal size).
int Map::getLines() const{
    return _lines;
}


