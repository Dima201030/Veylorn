// column - vertically (x axis)
// lines  - horizontally (y axis)

#pragma once

#include <cstddef>
#include <string>

#include "player.h"

enum class ErrorsCodeMap : int {
    OK = 0,
    NOFILE,
    NOAVAILABLE,

};

struct Map {

    explicit Map(std::string path);

    ~Map();

    bool isLoaded() const;

    ErrorsCodeMap getLastError() const;

    ErrorsCodeMap loadMapFile(std::string fileName);

    size_t getColumns() const;

    size_t getLines() const;

    void movePlayer(int posX, int posY);

    int operator()(size_t col, size_t line);
    int operator()(size_t col, size_t line) const;

    int *operator[](size_t col);
    const int *operator[](size_t col) const;

    std::string _serviceLine;
    std::string _errorFlag = "·";

    Player _player;

private:

    int       **_matrix  = nullptr;
    size_t      _column  = 0;
    size_t      _lines   = 0;

    ErrorsCodeMap _lastError = ErrorsCodeMap::OK;

    void allocateEmptyMatrix();

    void recreateMatrix();

    void recreateMatrix(int defaultValue);

    void setPlayer();

    void clearPlayer();

};
