#include "gtest/gtest.h"

#include "pathfinder.h"

#include <cassert>
#include <iostream>
#include <map>

const int mapWidth = 9;
const int mapHeight = 11;
const char *mapEtalon[mapHeight] =
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

/*TEST(TEST_pathfinder, test_pathfinder) {
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
    pathfinder::finderAdvance(posA.first, posA.second, map, mapPath);

    std::cout << std::endl;
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if ((int) mapPath[i][j] != 0)
                printf("%2d", (int) mapPath[i][j]);
            else
                printf("%2c", map[i][j]);
        }
        std::cout << std::endl;
    }
}*/

TEST(TEST_pathfinder, tmap) {
    pathfinder::TMap mazeMap = pathfinder::TMap::create(mapEtalon, mapWidth, mapHeight);
    mazeMap.print();
}

TEST(TEST_pathfinder, _getter) {
    pathfinder::TMap mazeMap = pathfinder::TMap::create(mapEtalon, mapWidth, mapHeight);

    EXPECT_EQ(mazeMap.getCell(1, 1), '%');
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

