#include <cstddef>
#include <fstream>
#include <string>

#include "map.h"
#include "lvlparser.h"

void parsePlayerFromServiceLine(const std::string &line, Player &player) {
    std::string key;
    std::string value;

    for (size_t i = 0; i < line.size(); ++i) {
        char ch = line[i];

        if (ch == '=') {
            value.clear();
            ++i;

            while (i < line.size() && line[i] != ',') {
                value += line[i];
                ++i;
            }

            if (key == "fpx") {
                player.posX = std::stoi(value);
            } else if (key == "fpy") {
                player.posY = std::stoi(value);
            } else if (key == "s") {
                player.ch = value[0];
            }
            key.clear();
        }
        else if (ch != ',') {
            key += ch;
        }
    }
}

std::string getServiceLine(std::string path) {
    std::fstream file(path);

    if (!file.is_open()) {
        return "";
    }

    std::string line;
    std::string lastNonEmpty;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            lastNonEmpty = line;
        }
    }

    return lastNonEmpty;
}

Map::Map(std::string path) : _matrix(nullptr), _column(0), _lines(0),  _lastError(ErrorsCodeMap::OK) {

    _lastError = loadMapFile(path);

    if (_lastError != ErrorsCodeMap::OK) {
        allocateEmptyMatrix();
    } else {
        _serviceLine = getServiceLine(path);
        parsePlayerFromServiceLine(_serviceLine, _player);
        parseObjects();
        setPlayer();
    }
}

Map::~Map() {
    for (size_t i = 0; i < _lines; ++i) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

void Map::parseObjects()
{
    // for (size_t y = 0; y < _column; ++y) {
    //     for (size_t x = 0; x < _lines; ++x) {
    //         switch (_matrix[x][y]) {
    //         case CellType::

    //             break;
    //         default:
    //             break;
    //         }
    //     }
    // }
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

ErrorsCodeMap Map::loadMapFile(std::string path) {
    ErrorsCodeMap checkMap = checkToValidMap(path);
    if (checkMap != ErrorsCodeMap::OK) {
        return checkMap;
    }

    std::fstream file(path, std::ios_base::in);

    if (!file.is_open()) {
        return ErrorsCodeMap::NOFILE;
    }

    _column = countColumns(path) - 1;
    _lines  = countSymblsInColumn(path);

    reCreateMatrix();

    std::string line;

    for (size_t y = 0; y < _column; ++y) {
        std::getline(file, line);
        for (size_t x = 0; x < _lines; ++x) {
            switch (char(line[x])) {
            case ' ':
                _matrix[x][y] = CELL_EMPTY;
                break;
            case '#':
                _matrix[x][y] = CELL_WALL;
                break;
            case '@':
                _matrix[x][y] = CELL_PLAYER;
                break;
            case '.':
                _matrix[x][y] = CELL_PLAYER_TRACE;
                break;
            default:
                _matrix[x][y] = CELL_UNKNOWN;
                break;
            }
        }
    }

    return ErrorsCodeMap::OK;
}

void Map::allocateEmptyMatrix() {
    _column = 1;
    _lines  = 1;

    _matrix = new CellType*[_lines];
    _matrix[0] = new CellType[_column]{CellType::CELL_EMPTY};
}

void Map::reCreateMatrix() {
    if (_matrix) {
        for (size_t i = 0; i < _lines; ++i) {
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }
    _matrix = new CellType*[_lines];

    for (size_t y = 0; y < _lines; ++y) {
        _matrix[y] = new CellType[_column];
        for (size_t x = 0; x < _column; ++x) {
            _matrix[y][x] = CellType::CELL_EMPTY;
        }
    }
}

void Map::reCreateMatrix(CellType defaultValue) {
    if (_matrix) {
        for (size_t i = 0; i < _lines; ++i) {
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }
    _matrix = new CellType*[_lines];

    for (size_t y = 0; y < _lines; ++y) {
        _matrix[y] = new CellType[_column];
        for (size_t x = 0; x < _column; ++x) {
            _matrix[y][x] = defaultValue;
        }
    }
}

int Map::operator()(size_t column, size_t lines) {
    return _matrix[lines][column];
}

int Map::operator()(size_t column, size_t lines) const {
    return _matrix[lines][column];
}

CellType *Map::operator[](size_t col) {
    return _matrix[col];
}

void Map::movePlayer(int posX, int posY, bool isRun) {
    if ((_player.posX + posX <= 0 && (posX != 1 && posX != -1))|| _player.posX + posX >= static_cast<int>(_lines)) {
        _errorFlag = "🛑";
        return;
    }
    if ((_player.posY + posY <= 0 && (posY != 1 && posY != -1))|| _player.posY + posY >= static_cast<int>(_column)) {
        _errorFlag = "🛑";
        return;
    }

    if (isRun) {
        if (posX == 2) {
            if (_matrix[_player.posX + 2][_player.posY] != '#') {
                if (_matrix[_player.posX + 1][_player.posY] != '#') {
                    _errorFlag = "·";
                    // if (_matrix[_player.posX + 2][_player.posY] == 'E') {
                    //     _errorFlag = "✅";
                    // }
                    _matrix[_player.posX][_player.posY] = CellType::CELL_PLAYER_TRACE;
                    _player.posX += 2;
                    _matrix[_player.posX - 1][_player.posY] = CellType::CELL_PLAYER_TRACE;
                    setPlayer();
                } else {
                    _errorFlag = "🛑";
                }
            } else  {
                movePlayer(posX - 1, posY, false);
            }
        } else if (posX == -2) {
            if (_matrix[_player.posX - 2][_player.posY] != '#') {
                if (_matrix[_player.posX - 1][_player.posY] != '#') {
                    _errorFlag = "·";
                    // if (_matrix[_player.posX + 2][_player.posY] == 'E') {
                    //     _errorFlag = "✅";
                    // }
                    _matrix[_player.posX][_player.posY] = CellType::CELL_PLAYER_TRACE;
                    _player.posX -= 2;
                    _matrix[_player.posX + 1][_player.posY] = CellType::CELL_PLAYER_TRACE;
                    setPlayer();
                } else {
                    _errorFlag = "🛑";
                }
            } else  {
                movePlayer(posX + 1, posY, false);
            }
        }
        if (posY == 2) {
            if (_matrix[_player.posX][_player.posY + 2] != '#') {
                if (_matrix[_player.posX][_player.posY + 1] != '#') {
                    _errorFlag = "·";
                    // if (_matrix[_player.posX + 2][_player.posY] == 'E') {
                    //     _errorFlag = "✅";
                    // }
                    _matrix[_player.posX][_player.posY] = CellType::CELL_PLAYER_TRACE;
                    _player.posY += 2;
                    _matrix[_player.posX][_player.posY - 1] = CellType::CELL_PLAYER_TRACE;
                    setPlayer();
                } else {
                    _errorFlag = "🛑";
                }
            } else  {
                movePlayer(posX, posY - 1, false);
            }
        } else if (posY == -2) {
            if (_matrix[_player.posX][_player.posY - 2] != '#') {
                if (_matrix[_player.posX][_player.posY - 1] != '#') {
                    _errorFlag = "·";
                    // if (_matrix[_player.posX + 2][_player.posY] == 'E') {
                    //     _errorFlag = "✅";
                    // }
                    _matrix[_player.posX][_player.posY] = CellType::CELL_PLAYER_TRACE;
                    _player.posY -= 2;
                    _matrix[_player.posX][_player.posY + 1] = CellType::CELL_PLAYER_TRACE;
                    setPlayer();
                } else {
                    _errorFlag = "🛑";
                }
            } else  {
                movePlayer(posX, posY + 1, false);
            }
        }
    } else {
        if (_matrix[_player.posX + posX][_player.posY + posY] != '#') {
            _errorFlag = "·";
            // if (_matrix[_player.posX + posX][_player.posY + posY] == 'E') {
            //     _errorFlag = "✅";
            // }
            _matrix[_player.posX][_player.posY] = CellType::CELL_PLAYER_TRACE;
            _player.posX += posX;
            _player.posY += posY;
            setPlayer();
        } else {
            _errorFlag = "🛑";
        }
    }
}

void Map::setPlayer()
{
    _matrix[_player.posX][_player.posY] = CellType::CELL_PLAYER;
}

const CellType *Map::operator[](size_t col) const {
    return _matrix[col];
}

size_t Map::getColumns() const{
    return _column;
}

size_t Map::getLines() const{
    return _lines;
}
