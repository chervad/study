#include "gtest/gtest.h"

#include "pathfinder.h"

#include <cassert>
#include <iostream>
#include <map>

using namespace pathfinder;

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

TEST(TEST_pathfinder, TMap_create_and_print) {
    TMap map = TMap::create(mapEtalon, mapWidth, mapHeight);
}

TEST(TEST_pathfinder, TMap_getter) {
    TMap map = TMap::create(mapEtalon, mapWidth, mapHeight);

    EXPECT_EQ(map.getCell(1, 1), '%');
    EXPECT_EQ(map.getCell(7, 1), '%');
    EXPECT_EQ(map.getCell(1, 7), '@');
    EXPECT_EQ(map.getCell(7, 6), '%');
    EXPECT_EQ(map.getCell(4, 9), '#');
}

TEST(TEST_pathfinder, TMap_searchFirstCell) {
    TMap map = TMap::create(mapEtalon, mapWidth, mapHeight);
    TPoint p = map.searchFirstCell('@');

    EXPECT_EQ(p, TPoint(1, 7));
}

TEST(TEST_pathfinder, TMap_searchAllCells) {
    TMap map = TMap::create(mapEtalon, mapWidth, mapHeight);
    std::list<TPoint> plist = map.searchAllCells('%');

    EXPECT_EQ(plist.size(), 3);
    uint8_t found = 0b00000000;
    for (const auto &item : plist) {
        if (item == TPoint(1, 1)) {
            found = found | 0b00000001;
        }
        if (item == TPoint(7, 1)) {
            found = found | 0b00000010;
        }
        if (item == TPoint(7, 6)) {
            found = found | 0b00000100;
        }
    }
    EXPECT_EQ(found, 0b00000111);
}

TEST(TEST_pathfinder, TMap_getPath) {
    TMap map = TMap::create(mapEtalon, mapWidth, mapHeight);
    TPoint p = map.searchFirstCell('@');
    TMap result = map.findAllPath(p);
    const char etalonDataSrc[11][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0}
    , {0, 0, 0, 16, 0, 16, 0, 0, 0}
    , {0, 13, 14, 15, 0, 15, 16, 17, 0}
    , {0, 12, 0, 16, 15, 14, 0, 0, 0}
    , {0, 11, 0, 0, 0, 13, 12, 0, 0}
    , {0, 10, 9, 8, 0, 0, 11, 0, 0}
    , {0, 0, 0, 7, 8, 9, 10, 0, 0}
    , {0, 0, 0, 6, 0, 0, 0, 12, 0}
    , {0, 1, 0, 5, 6, 7, 0, 11, 0}
    , {0, 2, 3, 4, 0, 8, 9, 10, 0}
    , {0, 0, 0, 0, 0, 0, 0, 0, 0}};
    char *etalon[mapHeight];// = (char **)malloc(mapHeight);
    for (int a = 0; a < mapHeight; ++a) {
        char *line = (char *)malloc(mapWidth);
        for (int b = 0; b < mapWidth; ++b) {
            line[b] = etalonDataSrc[a][b];
        }
        etalon[a] = line;
    }

    TMap expct = TMap::create((const char **)etalon, mapWidth, mapHeight);
    expct.print();
    EXPECT_EQ(result, expct);
    for (int a = 0; a < mapHeight; ++a) {
        free(etalon[a]);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

