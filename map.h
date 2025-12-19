// IN TEST
// column - vertically
// lines  - horizontally

#pragma once

#include <cstddef>

enum class ErrorsCode : int {
    OK = 0,
    NOFILE,
    BADFORMAT
};

struct Map {

    explicit Map(const char* fileName);


    bool isLoaded() const;
    ErrorsCode getLastError() const;

    ErrorsCode loadMapFile(const char* fileName);

    // Getters
    int getColumns() const;
    int getLines() const;

    // Access to column
    int operator()(int col, int line);
    const int operator()(int col, int line) const;

    // Access to lines
    int* operator[](int col);
    const int* operator[](int col) const;

private:

    int** _matrix = nullptr;
    int   _column = 0;
    int   _lines  = 0;

    ErrorsCode _lastError = ErrorsCode::OK;

    bool isCheckMapLevl();

    void allocateEmptyMatrix();

};
