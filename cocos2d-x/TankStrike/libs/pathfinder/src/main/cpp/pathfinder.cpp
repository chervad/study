//
// Created by 17385262 on 17.04.2019.
//
#include "pathfinder.h"

#include <iostream>
#include <cassert>
#include <map>
#include <queue>

#include <cstdlib>

struct tmap {
    uint8_t _width;
    uint8_t _height;
    char * const _data;
    size_t _size;

    tmap(uint8_t width, uint8_t height)
    : _width(width)
    , _height(height)
    , _size(width * height)
    , _data((char *)malloc(width * height))
    {}

    void set_data(char **data, uint8_t width, uint8_t height) {
        assert(_size == width * height);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int offset = width * i + j;
                _data[offset] = data[i][j];
            }
        }
    }

    char get(uint8_t x, uint8_t y) {
        int offset = _width * x + y;
        return _data[offset];
    }

    void set(uint8_t x, uint8_t y, char value) {
        int offset = _width * x + y;
        _data[offset] = value;
    }
};

static void finder_advance(int pX, int pY, const char map[11][10], char mapPath[11][10]) {
    struct tnode {
        int posX;
        int posY;
        int weight;

        tnode(int x, int y, int weight) : posX(x), posY(y), weight(weight) {}
    };

    tnode begin(pX, pY, 0);
    std::queue<tnode> nodes;
    nodes.push(begin);

    while(!nodes.empty()) {
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

static void finder(int posX, int posY, const char map[11][10], char mapPath[11][10], int loop) {
    if (map[posX - 1][posY] == ' ' &&  mapPath[posX - 1][posY] == 0) {
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

void PathFinder::Greet() {
    const int mapWidth=9;
    const int mapHeight=11;
    const char map[mapHeight][mapWidth + 1] =
            {"#########",
             "#%# # #%#",
             "#   #   #",
             "# #   ###",
             "# ###  ##",
             "#   ## ##",
             "###    %#",
             "#@# ### #",
             "# #   # #",
             "#   #   #",
             "#########"
            };
    char mapPath[mapHeight][mapWidth + 1] = {};

    std::pair<int, int> posA, posB;
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (map[i][j] == '%') {
                posB = std::make_pair(i, j);
            } else if (map[i][j] == '@') {
                posA = std::make_pair(i, j);
            }
        }
    }

    //finder(posA.first, posA.second, map, mapPath, 1);
    finder_advance(posA.first, posA.second, map, mapPath);

    std::cout << std::endl;
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if ((int)mapPath[i][j] != 0)
                printf("%2d", (int)mapPath[i][j]);
            else
                printf("%2c", map[i][j]);
        }
        std::cout << std::endl;
    }
}

int PathFinder::getNameLength() {
    return _name.length();
}
