// column - vertically (x axis)
// lines  - horizontally (y axis)

#pragma once

#include <cstddef>
#include <string>
#include <vector>

// #include "../objects/player.h"

// Forward declaration
struct Object;
struct Player;

enum class ErrorsCodeMap : int {
    OK = 0,
    NOFILE,
    NOAVAILABLE,

};

enum class CellType {
    EMPTY,
    WALL,
    PLAYER,
    TRACE,
    CHEST,
    GOLD
};

struct Map {

    explicit Map(std::string path, Player *player);

    ~Map();

    void parseObjects(std::string path);

    bool isLoaded() const;

    ErrorsCodeMap getLastError() const;

    ErrorsCodeMap loadMapFile(std::string fileName);

    size_t getColumns() const;

    size_t getLines() const;

    // Player
    Player *_player;

    void setPlayer();

    CellType operator()(size_t col, size_t line);
    CellType operator()(size_t col, size_t line) const;

    CellType *operator[](size_t col);
    const CellType *operator[](size_t col) const;

    std::string _serviceLine;
    std::string _errorFlag = "·";

    std::vector<Object> _objects;

private:

    CellType       **_matrix  = nullptr;
    size_t      _column  = 0;
    size_t      _lines   = 0;

    ErrorsCodeMap _lastError = ErrorsCodeMap::OK;

    void allocateEmptyMatrix();

    void reCreateMatrix();

    void reCreateMatrix(CellType defaultValue);

};
