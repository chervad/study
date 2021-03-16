#pragma once

#include <array>
#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

class Tank : public Sprite {
public:

	void update(float dt);

	void moveTo(eDirection direct);
	void moveTo(eDirection direct, int delta);
	void stop();

	virtual ~Tank();
protected:
	int nX_delta;
	int nY_delta;
	Size winSize;//пока как костыль для убыстрения работы update(), но как-то не красиво сделано
	int width;
	int height;
	float life = 100.f;

	eDirection direction;
	Animate *pMoveAnimate;
	uint8_t posiblePos; //bitmask

    virtual void initTank();
	virtual void initPhysics();
	virtual void playAnimation();
	virtual void pauseAnimation();
	bool checkMoveToPosition(eDirection dir);
};
