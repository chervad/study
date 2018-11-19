#pragma once

#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

class Tank : public Sprite {
public:

	void update(float dt);

	void moveTo(MoveDirection direct);
	void moveTo(MoveDirection direct, int delta);

	virtual ~Tank();
protected:
	int nX_delta;
	int nY_delta;
	Size winSize;
	int width;
	int height;

	MoveDirection eDirection;

	Animate *pMoveAnimate;

	void initTank();
	void initPhysics();
};
