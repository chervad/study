#include "Shot.h"

Shot *Shot::create(MoveDirection direction, const Vec2 &position)
{
	Shot *pShot = GameObject::create<Shot>();

	pShot->eDirection = direction;
	pShot->setPosition(position);
	pShot->initObject();
	pShot->initPhysics();
	return pShot;
}

void Shot::initPhysics() {
	Size size = this->getBoundingBox().size;
	size.width /= 3;
	size.height /= 3;
	PhysicsBody *physicsBody = PhysicsBody::createBox(size);
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0x0010);
	this->setPhysicsBody(physicsBody);
}

void Shot::update(float dt) {
	Vec2 position = getPosition();
	switch (eDirection) {
	case MoveDirection::LEFT:
		position.x -= 4;
		break;
	case MoveDirection::RIGHT:
		position.x += 4;
		break;
	case MoveDirection::UP:
		position.y += 4;
		break;
	case MoveDirection::DOWN:
		position.y -= 4;
		break;
	}
	setPosition(position);
}
