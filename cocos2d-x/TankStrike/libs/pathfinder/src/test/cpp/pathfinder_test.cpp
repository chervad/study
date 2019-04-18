//
// Created by 17385262 on 17.04.2019.
//
#include "gtest/gtest.h"

#include "pathfinder.h"

#include <cassert>
#include <iostream>

void testNameLength() {
    PathFinder pf("Caramba!");
    std::cout << "[test] returns the correct name length..." << std::flush;
    pf.Greet();
    assert(pf.getNameLength() == 8);
    std::cout << " pass" << std::endl;
}

TEST(Test01, TestMap) {
    PathFinder pf("Caramba!");
    pf.Greet();
    EXPECT_EQ(pf.getNameLength(), 8);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

