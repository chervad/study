#pragma once

#include "cocos2d.h"

#include "defens.h"
#include "Tank.h"
#include "Maze.h"
#include "Objectives/IObjective.h"

using namespace cocos2d;

class EnemyTank : public Tank {
public:
	static EnemyTank *create(Maze *pMaze);
	void startGameLoop();

	static std::tuple<uint16_t, uint16_t> convertPos2Area(Vec2 pos);
	static Vec2 convertArea2Pos(uint16_t areaX, uint16_t areaY);
	static Vec2 convertArea2Pos(std::tuple<uint16_t, uint16_t> area);

	virtual ~EnemyTank();

	//void update(float dt);
	void setObjective(IObjective *pObjctv);
protected:
    void calculateMove(int posX, int posY);
private:
	uint16_t targetAreaX;
	uint16_t targetAreaY;
    Maze *pMaze;

	void initTank(Maze *pMaze);
};
