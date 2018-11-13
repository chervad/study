#include "Wall.h"

void Wall::initObject() {
	PhysicsBody *physicsBody = PhysicsBody::createBox(this->getBoundingBox().size);
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0x0001);
	this->setPhysicsBody(physicsBody);
}
