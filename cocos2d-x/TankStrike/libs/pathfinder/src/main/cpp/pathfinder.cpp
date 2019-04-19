#include "pathfinder.h"

#include <cstdlib>
#include <iostream>

#include <cassert>
#include <queue>

using namespace pathfinder;

TMap::TMap(const char *data[], uint32_t width, uint32_t height)
: _width(width)
, _height(height)
, _size(width * height)
, _data((char *) malloc(width * height))
{
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            _data[width * i + j] = data[i][j];
        }
    }
}

TMap TMap::create(const char *data[], uint32_t width, uint32_t height) {
    assert(data != nullptr);
    return TMap(data, width, height);
}

char TMap::getCell(uint32_t x, uint32_t y) const {
    return _data[_width * x + y];
};

void TMap::setCell(uint32_t x, uint32_t y, char value) {
    _data[_width * x + y] = value;
}

void TMap::print() {
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            printf("%c", getCell(i, j));
        }
        printf("\n");
    }
}

void finder_advance(uint32_t pX, uint32_t pY, const char *map[10], char *mapPath[10]) {
    struct tnode {
        int posX;
        int posY;
        int weight;

        tnode(int x, int y, int weight) : posX(x), posY(y), weight(weight) {}
    };

    tnode begin(pX, pY, 0);
    std::queue<tnode> nodes;
    nodes.push(begin);

    while (!nodes.empty()) {
        tnode node = nodes.front();
        nodes.pop();
        if (map[node.posX - 1][node.posY] == ' ' && mapPath[node.posX - 1][node.posY] == 0) {
            tnode new_node(node.posX - 1, node.posY, node.weight + 1);
            mapPath[new_node.posX][new_node.posY] = new_node.weight;
            nodes.push(new_node);
        }
        if (map[node.posX][node.posY - 1] == ' ' && mapPath[node.posX][node.posY - 1] == 0) {
            tnode new_node(node.posX, node.posY - 1, node.weight + 1);
            mapPath[new_node.posX][new_node.posY] = new_node.weight;
            nodes.push(new_node);
        }
        if (map[node.posX + 1][node.posY] == ' ' && mapPath[node.posX + 1][node.posY] == 0) {
            tnode new_node(node.posX + 1, node.posY, node.weight + 1);
            mapPath[new_node.posX][new_node.posY] = new_node.weight;
            nodes.push(new_node);
        }
        if (map[node.posX][node.posY + 1] == ' ' && mapPath[node.posX][node.posY + 1] == 0) {
            tnode new_node(node.posX, node.posY + 1, node.weight + 1);
            mapPath[new_node.posX][new_node.posY] = new_node.weight;
            nodes.push(new_node);
        }
    }
}

void finder(uint32_t posX, uint32_t posY, const char map[11][10], char mapPath[11][10], int loop) {
    if (map[posX - 1][posY] == ' ' && mapPath[posX - 1][posY] == 0) {
        mapPath[posX - 1][posY] = loop;
        finder(posX - 1, posY, map, mapPath, loop + 1);
    }
    if (map[posX][posY - 1] == ' ' && mapPath[posX][posY - 1] == 0) {
        mapPath[posX][posY - 1] = loop;
        finder(posX, posY - 1, map, mapPath, loop + 1);
    }
    if (map[posX + 1][posY] == ' ' && mapPath[posX + 1][posY] == 0) {
        mapPath[posX + 1][posY] = loop;
        finder(posX + 1, posY, map, mapPath, loop + 1);
    }
    if (map[posX][posY + 1] == ' ' && mapPath[posX][posY + 1] == 0) {
        mapPath[posX][posY + 1] = loop;
        finder(posX, posY + 1, map, mapPath, loop + 1);
    }
}
