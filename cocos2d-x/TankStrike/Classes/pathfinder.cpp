#include "pathfinder.h"

#include <cstdlib>
#include <iostream>
#include <cstring>

#include <cassert>
#include <queue>
#include <sstream>

#include "cocos2d.h"

using namespace pathfinder;

size_t TMap::offset(uint32_t x, uint32_t y) const {
    return _width * y + x;//26 * 16 + 23 = 416 + 16 = 432
}

TMap::TMap(const char *data[], uint32_t width, uint32_t height)
: _width(width)
, _height(height)
, _size(width * height)
, _data((uint8_t *) malloc(width * height))
{
    size_t offset = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            _data[offset] = (uint8_t)data[i][j];
            offset++;
        }
    }
}

TMap::TMap(uint32_t width, uint32_t height)
: _width(width)
, _height(height)
, _size(width * height)
, _data((uint8_t *) malloc(width * height))
{
    memset(_data, 0, _size);
}

TMap TMap::create(const char *data[], uint32_t width, uint32_t height) {
    assert(data != nullptr);
    return TMap(data, width, height);
}

bool TMap::operator==(const TMap &b) const {
    if (_width != b._width) return false;
    if (_height != b._height) return false;
    if (_size != b._size) return false;
    for (int a = 0; a < _size; ++a) {
        if (_data[a] != b._data[a]) return false;
    }
    return true;
}

char TMap::getCell(uint32_t x, uint32_t y) const {
    if (x > _width) return 0;
    if (y > _height) return 0;
    return _data[offset(x, y)];
};

void TMap::setCell(uint32_t x, uint32_t y, char value) {
    _data[offset(x, y)] = value;
}

void TMap::print() {
    cocos2d::log("TMap(0x%x)[%d x %d] size %d\n", this, _width, _height, _size);
    size_t sz = 1024;
    char *buffer = (char *)malloc(sz);
    memset(buffer, 0, sz);
    char *p_buffer = buffer;
    sprintf(p_buffer, "   ");
    p_buffer += 3;
    for (int i = 0; i < _width; ++i) {
        sprintf(p_buffer, "|%2d", i);
        p_buffer += 3;
    }
    cocos2d::log("%s|", buffer);
    memset(buffer, 0, sz);
    p_buffer = buffer;
    sprintf(p_buffer, "|--");
    p_buffer += 3;
    for (int i = 0; i < _width; ++i) {
        sprintf(p_buffer, "|--", i);
        p_buffer += 3;
    }
    cocos2d::log("%s|", buffer);
    for (int j = 0; j < _height; ++j) {
        memset(buffer, 0, sz);
        p_buffer = buffer;
        sprintf(p_buffer, "|%2d", j);
        p_buffer += 3;
        for (int i = 0; i < _width; ++i) {
            sprintf(p_buffer, "|%2d", _data[offset(i, j)]);
            p_buffer += 3;
        }
        cocos2d::log("%s|", buffer);
    }
    free(buffer);
}

TPoint TMap::searchFirstCell(char val) const {
    TPoint pos;
    for (int i = 0; i < _width; ++i) {
        for (int j = 0; j < _height; ++j) {
            if (getCell(i, j) == val) {
                pos._x = i;
                pos._y = j;
                break;
            }
        }
    }
    return pos;
}

std::list<TPoint> TMap::searchAllCells(char val) const {
    std::list<TPoint> res;
    for (int i = 0; i < _width; ++i) {
        for (int j = 0; j < _height; ++j) {
            if (getCell(i, j) == val) {
                TPoint pos;
                pos._x = i;
                pos._y = j;
                res.push_back(pos);
            }
        }
    }
    return res;
}

TMap TMap::findAllPath(const TPoint &point_begin) {
    struct tnode {
        int posX;
        int posY;
        int weight;

        tnode(int x, int y, int weight) : posX(x), posY(y), weight(weight) {}
    };

    TMap mapPath = TMap(_width, _height);

    tnode begin(point_begin._x, point_begin._y, 0);
    std::queue<tnode> nodes;
    nodes.push(begin);

    while (!nodes.empty()) {
        tnode node = nodes.front();
        nodes.pop();
        if (node.posX > 0 && getCell(node.posX - 1, node.posY) == ' ' && mapPath.getCell(node.posX - 1, node.posY) == 0) {
            tnode new_node(node.posX - 1, node.posY, node.weight + 1);
            mapPath.setCell(new_node.posX, new_node.posY, new_node.weight);
            nodes.push(new_node);
        }
        if (node.posY > 0 && getCell(node.posX, node.posY - 1) == ' ' && mapPath.getCell(node.posX, node.posY - 1) == 0) {
            tnode new_node(node.posX, node.posY - 1, node.weight + 1);
            mapPath.setCell(new_node.posX, new_node.posY, new_node.weight);
            nodes.push(new_node);
        }
        if (node.posX < (_width - 1) && getCell(node.posX + 1, node.posY) == ' ' && mapPath.getCell(node.posX + 1, node.posY) == 0) {
            tnode new_node(node.posX + 1, node.posY, node.weight + 1);
            mapPath.setCell(new_node.posX, new_node.posY, new_node.weight);
            nodes.push(new_node);
        }
        char c = getCell(node.posX, node.posY + 1);
        char m = mapPath.getCell(node.posX, node.posY + 1);
        if (node.posY < (_height - 1) && c == ' ' && m == 0) {
            tnode new_node(node.posX, node.posY + 1, node.weight + 1);
            mapPath.setCell(new_node.posX, new_node.posY, new_node.weight);
            nodes.push(new_node);
        }
    }

    return mapPath;
}

/*void TMap::findAllPath(uint32_t pBeginX, uint32_t pBeginY, char **mapPath) {
    struct tnode {
        int posX;
        int posY;
        int weight;

        tnode(int x, int y, int weight) : posX(x), posY(y), weight(weight) {}
    };

    tnode begin(pBeginX, pBeginY, 0);
    std::queue<tnode> nodes;
    nodes.push(begin);

    while (!nodes.empty()) {
        tnode node = nodes.front();
        nodes.pop();
        if (node.posX > 0 && getCell(node.posX - 1, node.posY) == ' ' && mapPath[node.posX - 1][node.posY] == 0) {
            tnode new_node(node.posX - 1, node.posY, node.weight + 1);
            mapPath[new_node.posX][new_node.posY] = new_node.weight;
            nodes.push(new_node);
        }
        if (node.posY > 0 && getCell(node.posX, node.posY - 1) == ' ' && mapPath[node.posX][node.posY - 1] == 0) {
            tnode new_node(node.posX, node.posY - 1, node.weight + 1);
            mapPath[new_node.posX][new_node.posY] = new_node.weight;
            nodes.push(new_node);
        }
        if (node.posX < (_width - 1) && getCell(node.posX + 1, node.posY) == ' ' && mapPath[node.posX + 1][node.posY] == 0) {
            tnode new_node(node.posX + 1, node.posY, node.weight + 1);
            mapPath[new_node.posX][new_node.posY] = new_node.weight;
            nodes.push(new_node);
        }
        char c = getCell(node.posX, node.posY + 1);
        char m = mapPath[node.posX][node.posY + 1];
        if (node.posY < (_height - 1) && c == ' ' && m == 0) {
            tnode new_node(node.posX, node.posY + 1, node.weight + 1);
            mapPath[new_node.posX][new_node.posY] = new_node.weight;
            nodes.push(new_node);
        }
    }
}*/

void pathfinderRecurse(uint32_t posX, uint32_t posY, const char map[11][10], char mapPath[11][10], int loop) {
    if (map[posX - 1][posY] == ' ' && mapPath[posX - 1][posY] == 0) {
        mapPath[posX - 1][posY] = loop;
        pathfinderRecurse(posX - 1, posY, map, mapPath, loop + 1);
    }
    if (map[posX][posY - 1] == ' ' && mapPath[posX][posY - 1] == 0) {
        mapPath[posX][posY - 1] = loop;
        pathfinderRecurse(posX, posY - 1, map, mapPath, loop + 1);
    }
    if (map[posX + 1][posY] == ' ' && mapPath[posX + 1][posY] == 0) {
        mapPath[posX + 1][posY] = loop;
        pathfinderRecurse(posX + 1, posY, map, mapPath, loop + 1);
    }
    if (map[posX][posY + 1] == ' ' && mapPath[posX][posY + 1] == 0) {
        mapPath[posX][posY + 1] = loop;
        pathfinderRecurse(posX, posY + 1, map, mapPath, loop + 1);
    }
}
