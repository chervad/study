#include "Tank.h"

#include "TextureFactory.h"

Tank::~Tank()
{
	CC_SAFE_RELEASE(pMoveAnimate);
}

void Tank::moveTo(MoveDirection direct) {
	moveTo(direct, DELTA);
}

void Tank::moveTo(MoveDirection direct, int delta) {
	//eDirection = direct;
	if (direct == MoveDirection::LEFT || direct == MoveDirection::RIGHT) {
		nY_delta = 0;
	}
	if (direct == MoveDirection::UP || direct == MoveDirection::DOWN) {
		nX_delta = 0;
	}
	switch (direct) {
	case MoveDirection::LEFT:
		setRotation(-90.0f);
		nX_delta = -1 * delta;
		break;
	case MoveDirection::RIGHT:
		setRotation(90.0f);
		nX_delta = delta;
		break;
	case  MoveDirection::UP:
		setRotation(0.0f);
		nY_delta = delta;
		break;
	case  MoveDirection::DOWN:
		setRotation(180.0f);
		nY_delta = -1 * delta;
		break;
	}
}

void Tank::update(float dt)
{
	if (nX_delta != 0 || nY_delta != 0) {
		Point p = getPosition();
		Size size = Director::getInstance()->getWinSize();

		if (p.x + nX_delta > DELTA && p.x + nX_delta < size.width - DELTA &&
			p.y + nY_delta > DELTA && p.y + nY_delta < size.height - DELTA)
		{
			setPosition(Vec2(p.x + nX_delta, p.y + nY_delta));
		}
		//runMoveAnimate();
		if (pMoveAnimate->getTarget() != nullptr) {
			getActionManager()->resumeTarget(this);
		}
		else {
			auto a = runAction(RepeatForever::create(pMoveAnimate));
		}
	}
	if (nX_delta == 0 && nY_delta == 0) {
		//stopMoveAnimate();
		getActionManager()->pauseTarget(this);
	}
}
