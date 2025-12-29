// column - vertically (x axis)
// lines  - horizontally (y axis)

#pragma once

#include <cstddef>

// Enum representing possible error codes for map operations
enum class ErrorsCodeMap : int {
    OK = 0,         // No errors
    NOFILE,         // File not found
    NOAVAILABLE,    // Map is invalid or unavailable

};

// Structure representing a 2D map with dynamic allocation
struct Map {

    // Constructor: loads the map from the given file name
    explicit Map(const char *fileName);

    // Destructor: frees allocated memory
    ~Map();

    // Checks if the map is successfully loaded
    bool isLoaded() const;

    // Returns the last error code
    ErrorsCodeMap getLastError() const;

    // Loads the map from a file and validates it
    ErrorsCodeMap loadMapFile(const char *fileName);

    // Getters
    // Get the number of columns (vertical size)
    int getColumns() const;

    // Get the number of lines (horizontal size)
    int getLines() const;

    // Access a specific cell: first argument is column (x), second is line (y)
    int operator()(int col, int line);
    const int operator()(int col, int line) const;

    // Access a full column
    int *operator[](int col);
    const int *operator[](int col) const;

private:

    int **_matrix = nullptr;    // 2D array storing map values
    int   _column = 0;          // Number of columns
    int   _lines  = 0;          // Number of lines

    // Last error state
    ErrorsCodeMap _lastError = ErrorsCodeMap::OK;

    // Allocates an empty matrix with current size
    void allocateEmptyMatrix();

    // Recreates the matrix without default values
    void recreateMatrix();

    // Recreates the matrix and fills with defaultValue
    void recreateMatrix(int defaultValue);

};
