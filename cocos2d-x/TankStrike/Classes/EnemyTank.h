#pragma once

#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

class EnemyTank : public Sprite {
public:
	enum class MoveDirection {
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
public:
	static EnemyTank *create();

	static std::tuple<uint16_t, uint16_t> convertPos2Area(Vec2 pos);
	static Vec2 convertArea2Pos(uint16_t areaX, uint16_t areaY);
	static Vec2 convertArea2Pos(std::tuple<uint16_t, uint16_t> area);

	void update(float dt);

	//void stopMove();
	void moveTo(MoveDirection direct);
	void moveTo(MoveDirection direct, int deltaPixels);
	void moveToArea(MoveDirection direct, int deltaArea);
	//void moveTo(int deltaX, int deltaY);

private:
	int nX_delta;
	int nY_delta;
	//MoveDirection eDirection;
	uint16_t targetAreaX;
	uint16_t targetAreaY;

	Animate *pMoveAnimate;

	~EnemyTank();
	void initTank();

	//void runMoveAnimate();
	//void stopMoveAnimate();
};
