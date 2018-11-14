#include "Tank.h"
#include "Maze.h"

#include "TextureFactory.h"

using namespace cocos2d;

Tank::~Tank()
{
	CC_SAFE_RELEASE(pMoveAnimate);
}


void Tank::initPhysics() {
	PhysicsBody *physicsBody = PhysicsBody::createBox(this->getBoundingBox().size);
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0x0010);
	this->setPhysicsBody(physicsBody);
}

void Tank::moveTo(MoveDirection direct) {
	moveTo(direct, DELTA);
}

void Tank::moveTo(MoveDirection direct, int delta) {
	eDirection = direct;
	if (direct == MoveDirection::LEFT || direct == MoveDirection::RIGHT) {
		nY_delta = 0;
	}
	if (direct == MoveDirection::UP || direct == MoveDirection::DOWN) {
		nX_delta = 0;
	}
	switch (eDirection) {
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
		Point curPos = this->getPosition();
		Size size = Director::getInstance()->getWinSize();

		if (curPos.x + nX_delta > DELTA && curPos.x + nX_delta < size.width - DELTA &&
			curPos.y + nY_delta > DELTA && curPos.y + nY_delta < size.height - DELTA)
		{
			Vec2 newPos = Vec2(curPos.x + nX_delta, curPos.y + nY_delta);
			if (Maze::moveTankThisPosition(curPos, newPos, this->getBoundingBox().size, this->eDirection)) {
				setPosition(newPos);
			}
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
