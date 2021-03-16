#include <cmath>
#include <random>

#include "Tank.h"
#include "Maze.h"
#include "EnemyTank.h"

#include "TextureFactory.h"

using namespace cocos2d;

int getRandom(int a, int b) {
	std::random_device random_device; // Источник энтропии.
	std::mt19937 generator(random_device()); // Генератор случайных чисел.
	std::uniform_int_distribution<> distribution(a, b); // Равномерное распределение [10, 20]

	return distribution(generator); // Случайное число.
}

Tank::~Tank()
{
	CC_SAFE_RELEASE(pMoveAnimate);
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
	//this->playAnimation();
	//pauseAnimation();
}

void Tank::stop() {
	if (this->direction == eDirection::LEFT || this->direction == eDirection::RIGHT) {
		nX_delta = 0;
        log("stop x");
	}
	if (this->direction == eDirection::UP || this->direction == eDirection::DOWN) {
		nY_delta = 0;
        log("stop y");
	}
}

void Tank::playAnimation() {
	//todo: почему-то анимация вызывает жесткий эксепшн!
	//return;
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
	//return;
	if (nX_delta == 0 && nY_delta == 0) {
		getActionManager()->pauseTarget(this);
	}
}

bool Tank::checkMoveToPosition(eDirection dir) {
	const Point curPos = this->getPosition();
	int dx = 0;
	int dy = 0;
	switch (dir) {
	case eDirection::LEFT:  dx -= DELTA;  break;
	case eDirection::RIGHT: dx += DELTA;  break;
	case eDirection::UP:    dy += DELTA;  break;
	case eDirection::DOWN:  dy -= DELTA;  break;
	}
	Vec2 newPos = Vec2(curPos.x + dx, curPos.y + dy);
	return Maze::moveTankThisPosition(newPos, this->width, this->height, dir);
}

void Tank::update(float dt)
{
	if (nX_delta != 0 || nY_delta != 0) {
		Point curPos = this->getPosition();

		if (curPos.x + nX_delta > DELTA && curPos.x + nX_delta < winSize.width - DELTA &&
			curPos.y + nY_delta > DELTA && curPos.y + nY_delta < winSize.height - DELTA)
		{
			Vec2 newPos = Vec2(curPos.x + nX_delta, curPos.y + nY_delta);
			if (Maze::moveTankThisPosition(newPos, this->width, this->height, this->direction)) {
				this->setPosition(newPos);
			}
			else {
				this->posiblePos = 0;
				for (uint8_t d = eDirection::LEFT; d <= eDirection::DOWN; d = d << 1 ) {
					if (direction != (eDirection)d && checkMoveToPosition((eDirection)d)) {
						this->posiblePos = this->posiblePos | d;
					}
				}
				if (this->posiblePos != 0) {
					int newDir = 0;
					while (newDir == 0) {
						newDir = this->posiblePos & (1 << getRandom(0, 3));
					}
					moveTo((eDirection)newDir);
				}
			}
			int r = getRandom(0, 10000);
			if (r % 100 == 0) {
				this->posiblePos = 0;
				for (uint8_t d = eDirection::LEFT; d <= eDirection::DOWN; d = d << 1) {
					if (checkMoveToPosition((eDirection)d)) {
						this->posiblePos = this->posiblePos | d;
					}
				}
				if (this->posiblePos != 0) {
					int newDir = 0;
					while (newDir == 0) {
						newDir = this->posiblePos & (1 << getRandom(0, 3));
					}
					moveTo((eDirection)newDir);
				}
			}
		}
	}
}
