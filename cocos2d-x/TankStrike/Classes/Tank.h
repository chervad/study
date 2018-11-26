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
	Size winSize;//пока как костыль для убыстрения работы update(), но как-то не красиво сделано
	int width;
	int height;
	float life = 100.f;
	float damage_koef = .75f;

	MoveDirection eDirection;

	Animate *pMoveAnimate;

	void initTank();
	void initPhysics();
	virtual void playAnimation();
	virtual void pauseAnimation();
};
