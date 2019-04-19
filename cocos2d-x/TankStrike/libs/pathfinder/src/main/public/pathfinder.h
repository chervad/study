#ifndef TANKSTRIKE_PATHFINDER_H
#define TANKSTRIKE_PATHFINDER_H

#include <cstdint>

#if defined(DLL_EXPORT)
#  define DECLSPEC __declspec(dllexport)
#else
#  define DECLSPEC
#endif //defined(DLL_EXPORT)

namespace pathfinder {

    struct DECLSPEC TPoint {
        uint32_t _x;
        uint32_t _y;

        TPoint(uint32_t x, uint32_t y) : _x(x), _y(y) {}
    };

    class DECLSPEC TMap {
    private:
        uint32_t _width;
        uint32_t _height;

        //Можно заменить на Boost.MultiArray
        // https://www.boost.org/doc/libs/1_70_0/libs/multi_array/doc/index.html
        char * const _data;
        size_t _size;

        TMap(const char *data[], uint32_t width, uint32_t height);
    public:
        static TMap create(const char *data[], uint32_t width, uint32_t height);

        char getCell(uint32_t x, uint32_t y) const;
        void setCell(uint32_t x, uint32_t y, char value);

        void print();
    };

    void finderAdvance(uint32_t pX, uint32_t pY, const char **map, char **mapPath);

    void finder(uint32_t posX, uint32_t posY, const char map[11][10], char mapPath[11][10], uint32_t loop);

}
#endif //TANKSTRIKE_PATHFINDER_H
