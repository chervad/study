//
// Created by 17385262 on 17.04.2019.
//

#ifndef TANKSTRIKE_PATHFINDER_H
#define TANKSTRIKE_PATHFINDER_H

#include <string>
#include <algorithm>

#if defined(DLL_EXPORT)
#  define DECLSPEC __declspec(dllexport)
#else
#  define DECLSPEC
#endif //defined(DLL_EXPORT)

class DECLSPEC PathFinder {
public:
    explicit PathFinder(const std::string &name) : _name(name) {};
    PathFinder() : _name("World") {};
    void Greet();
    int getNameLength();
private:
    std::string _name;
};

#endif //TANKSTRIKE_PATHFINDER_H
