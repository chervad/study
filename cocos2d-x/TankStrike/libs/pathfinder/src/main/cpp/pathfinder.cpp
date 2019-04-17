//
// Created by 17385262 on 17.04.2019.
//
#include "pathfinder.h"

#include <iostream>
#include <map>

void PathFinder::Greet() {
    const int mapWidth=9;
    const int mapHeight=11;
    const char map[mapHeight][mapWidth + 1] =
            {"#########",
             "# # # #%#",
             "# # #   #",
             "# #   ###",
             "# ###  ##",
             "### #####",
             "###     #",
             "#@##### #",
             "# #   # #",
             "#   #   #",
             "#########"
            };
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
    char mapPath[mapHeight][mapWidth + 1] = {};
    int loop = 1;
    if (map[posA.first - 1][posA.second] == ' ') {
        mapPath[posA.first - 1][posA.second] = loop;
    }
    if (map[posA.first][posA.second - 1] == ' ') {
        mapPath[posA.first][posA.second - 1] = loop;
    }
    if (map[posA.first + 1][posA.second] == ' ') {
        mapPath[posA.first][posA.second - 1] = loop;
    }
    if (map[posA.first][posA.second - 1] == ' ') {
        mapPath[posA.first][posA.second - 1] = loop;
    }
    loop++;
}

int PathFinder::getNameLength() {
    return _name.length();
}
