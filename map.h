// column - vertically (x axis)
// lines  - horizontally (y axis)

#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "player.h"
#include "object.h"

enum class ErrorsCodeMap : int {
    OK = 0,
    NOFILE,
    NOAVAILABLE,

};

enum CellType {
    CELL_EMPTY = 32,
    CELL_WALL  = 35,
    CELL_PLAYER = 64,
    CELL_PLAYER_TRACE = 46,
    CELL_UNKNOWN = -1
};

struct Map {

    explicit Map(std::string path);

    ~Map();

    void parseObjects();

    bool isLoaded() const;

    ErrorsCodeMap getLastError() const;

    ErrorsCodeMap loadMapFile(std::string fileName);

    size_t getColumns() const;

    size_t getLines() const;

    void movePlayer(int x, int y, bool isRun = false);

    int operator()(size_t col, size_t line);
    int operator()(size_t col, size_t line) const;

    CellType *operator[](size_t col);
    const CellType *operator[](size_t col) const;

    std::string _serviceLine;
    std::string _errorFlag = "·";

    Player _player;
    std::vector<ObjectType> objects;

private:

    CellType       **_matrix  = nullptr;
    size_t      _column  = 0;
    size_t      _lines   = 0;

    ErrorsCodeMap _lastError = ErrorsCodeMap::OK;

    void allocateEmptyMatrix();

    void reCreateMatrix();

    void reCreateMatrix(CellType defaultValue);

    void setPlayer();

    bool tryMove(int x, int y);

};
