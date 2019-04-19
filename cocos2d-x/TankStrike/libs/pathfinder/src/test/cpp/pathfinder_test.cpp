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
char mapPath[mapHeight][mapWidth + 1] = {};

TEST(TEST_pathfinder, TMap_create_and_print) {
    TMap map = TMap::create(mapEtalon, mapWidth, mapHeight);
    map.print();
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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

