//https://developercommunity.visualstudio.com/content/problem/303465/inability-to-install-build-tools-for-visual-studio.html
//https://docs.microsoft.com/ru-ru/visualstudio/install/build-tools-container?cid=kerryherger&view=vs-2017
//https://devblogs.microsoft.com/cppblog/visual-studio-build-tools-now-include-the-vs2017-and-vs2015-msvc-toolsets/

#ifndef TANKSTRIKE_PATHFINDER_H
#define TANKSTRIKE_PATHFINDER_H

#include <cstdint>
#include <cstdio>
#include <list>

#if defined(DLL_EXPORT)
#  define DECLSPEC __declspec(dllexport)
#else
#  define DECLSPEC
#endif //defined(DLL_EXPORT)

namespace pathfinder {

    struct DECLSPEC TPoint {
        uint32_t _x;
        uint32_t _y;

        TPoint() : _x(UINT32_MAX), _y(UINT32_MAX) {}
        TPoint(uint32_t x, uint32_t y) : _x(x), _y(y) {}

        bool operator==(const TPoint &b) const {
            return _x == b._x && _y == b._y;
        }
    };

    class DECLSPEC TMap {
    private:
        //Можно заменить на Boost.MultiArray
        // https://www.boost.org/doc/libs/1_70_0/libs/multi_array/doc/index.html
        char * const _data;
        size_t _size;

        const uint32_t _width;
        const uint32_t _height;

        TMap(const char *data[], uint32_t width, uint32_t height);
        TMap(uint32_t width, uint32_t height);

        size_t offset(uint32_t x, uint32_t y) const;
    public:
        static TMap create(const char *data[], uint32_t width, uint32_t height);
        bool operator==(const TMap &b) const;

        char getCell(uint32_t x, uint32_t y) const;
        void setCell(uint32_t x, uint32_t y, char value);

        TPoint searchFirstCell(char etalon) const;
        std::list<TPoint> searchAllCells(char etalon) const;

        //void findAllPath(uint32_t pBeginX, uint32_t pBeginY, char **mapPath);
        TMap findAllPath(const TPoint &begin);

        void print();
        void fprintc(FILE *fl);
        void fprintd(FILE *fl);
    };

    void pathfinderRecurse(uint32_t posX, uint32_t posY, const char map[11][10], char mapPath[11][10], uint32_t loop);

}
#endif //TANKSTRIKE_PATHFINDER_H
