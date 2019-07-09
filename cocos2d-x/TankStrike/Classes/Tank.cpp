#include "Tank.h"
#include "Maze.h"
#include "EnemyTank.h"

#include "TextureFactory.h"

using namespace cocos2d;

Tank::~Tank()
{
	CC_SAFE_RELEASE(pMoveAnimate);
}

void Tank::setNearbyObj(eDirection direction, ObjType objType) {
	this->nearbyObj[direction] = objType;
}

void Tank::initTank() {
	this->winSize = Director::getInstance()->getWinSize();
	Size size = this->getBoundingBox().size;
	this->width = (size.width - 6) / 2;
	this->height = (size.height - 6) / 2;
}

void Tank::initPhysics() {
	PhysicsBody *physicsBody = PhysicsBody::createBox(this->getBoundingBox().size);
	physicsBody->setDynamic(false);
	//physicsBody->setContactTestBitmask(0b00000000);
	this->setPhysicsBody(physicsBody);
}

void Tank::moveTo(eDirection direct) {
	moveTo(direct, DELTA);
}

void Tank::moveTo(eDirection direct, int delta) {
	direction = direct;
	if (direct == eDirection::LEFT || direct == eDirection::RIGHT) {
		nY_delta = 0;
	}
	if (direct == eDirection::UP || direct == eDirection::DOWN) {
		nX_delta = 0;
	}
	switch (direction) {
	case eDirection::LEFT:
		setRotation(-90.0f);
		nX_delta = -1 * delta;
		break;
	case eDirection::RIGHT:
		setRotation(90.0f);
		nX_delta = delta;
		break;
	case  eDirection::UP:
		setRotation(0.0f);
		nY_delta = delta;
		break;
	case  eDirection::DOWN:
		setRotation(180.0f);
		nY_delta = -1 * delta;
		break;
	}
	this->playAnimation();
	pauseAnimation();
}

void Tank::stop() {
	if (this->direction == eDirection::LEFT || this->direction == eDirection::RIGHT) {
		nX_delta = 0;
	}
	if (this->direction == eDirection::UP || this->direction == eDirection::DOWN) {
		nY_delta = 0;
	}
}

void Tank::playAnimation() {
	//todo: почему-то анимация вызывает жесткий эксепшн!
	return;
	if (nX_delta != 0 || nY_delta != 0) {
		if (pMoveAnimate->getTarget() != nullptr) {
			getActionManager()->resumeTarget(this);
		}
		else {
			Action* action = RepeatForever::create(pMoveAnimate);
			auto a = runAction(action);
		}
	}
}

void Tank::pauseAnimation() {
	//todo: почему-то анимация вызывает жесткий эксепшн!
	return;
	if (nX_delta == 0 && nY_delta == 0) {
		getActionManager()->pauseTarget(this);
	}
}

void Tank::update(float dt)
{
	if (nX_delta != 0 || nY_delta != 0) {
		Point curPos = this->getPosition();

		if (curPos.x + nX_delta > DELTA && curPos.x + nX_delta < winSize.width - DELTA &&
			curPos.y + nY_delta > DELTA && curPos.y + nY_delta < winSize.height - DELTA)
		{
			Vec2 newPos = Vec2(curPos.x + nX_delta, curPos.y + nY_delta);
			//if (Maze::moveTankThisPosition(newPos, this->width, this->height, this->direction)) {
				this->setPosition(newPos);

                std::tuple<uint16_t, uint16_t> post = EnemyTank::convertPos2Area(newPos);
                this->posX = std::get<0>(post);
                this->posY = 19 - std::get<1>(post) - 1;
			//}
		}
	}
}
