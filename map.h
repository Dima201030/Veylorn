// IN TEST
// column - vertically (x axis)
// lines  - horizontally (y axis)

#pragma once

#include <cstddef>

enum class ErrorsCodeMap : int {
    OK = 0,
    NOFILE,
    NOAVAILABLE,

};

struct Map {

    explicit Map(const char *fileName);
    ~Map();

    bool isLoaded() const;
    ErrorsCodeMap getLastError() const;

    ErrorsCodeMap loadMapFile(const char *fileName);

    // Getters
    int getColumns() const;
    int getLines() const;

    // Access to column. First elem - (x axis), second elem - (y axis)
    int operator()(int col, int line);
    const int operator()(int col, int line) const;

    // Access to lines
    int *operator[](int col);
    const int *operator[](int col) const;

private:

    int **_matrix = nullptr;
    int   _column = 0;
    int   _lines  = 0;

    ErrorsCodeMap _lastError = ErrorsCodeMap::OK;

    void allocateEmptyMatrix();

    void recreateMatrix();
    void recreateMatrix(int defaultValue);

};
