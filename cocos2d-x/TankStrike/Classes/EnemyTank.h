#pragma once

#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

class EnemyTank : public Sprite {
public:
	Animate * moveAnimate;

	static EnemyTank *create(void);

	void move(int directionParam);

	void idle();

	void update();

private:
	~EnemyTank();

	bool moving;

	int direction;

	void initPlayer();
};
