//
// Created by 17385262 on 17.04.2019.
//
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

int main(int argc, char **argv) {
    testNameLength();
    return 0;
}
