#pragma once

#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

class Tank : public Sprite {
public:

	void update(float dt);

	void moveTo(eDirection direct);
	void moveTo(eDirection direct, int delta);

	virtual ~Tank();
protected:
	int nX_delta;
	int nY_delta;
	Size winSize;//���� ��� ������� ��� ���������� ������ update(), �� ���-�� �� ������� �������
	int width;
	int height;
	float life = 100.f;
	float damage_koef = .75f;
	int posX;
	int posY;

	eDirection direction;

	Animate *pMoveAnimate;

	void initTank();
	void initPhysics();
	virtual void playAnimation();
	virtual void pauseAnimation();
};
