#pragma once
#include "cocos2d.h"

#include "defens.h"
#include "Tank.h"
#include "Maze.h"
#include "Objectives/IObjective.h"

using namespace cocos2d;

class EnemyTank : public Tank {
public:
	static EnemyTank *create();
	/**
	 * преобразовываем координаты спрайта на экране к координатам карты
	 * @param pos
	 * @return
	 */
	static std::tuple<uint16_t, uint16_t> convertPos2Area(Vec2 pos);
	/**
	 * считаем погрешность преобразования координаты спрайта на экране к координатам карты
	 * @param pos
	 * @return
	 */
    static bool accurancyPosition(Vec2 pos);
    /**
     * преобразование координаты карты к координатам экрана
     * @param areaX
     * @param areaY
     * @return
     */
	static Vec2 convertArea2Pos(uint16_t areaX, uint16_t areaY);
    /**
     * преобразование координаты карты к координатам экрана
     * @param area
     * @return
     */
	static Vec2 convertArea2Pos(std::tuple<uint16_t, uint16_t> area);

	virtual ~EnemyTank();
private:
	void initTank();
};
