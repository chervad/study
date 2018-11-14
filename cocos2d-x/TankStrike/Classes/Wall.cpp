#include "Wall.h"

void Wall::initObject() {
	this->initPhysics();
}

void Wall::initPhysics() {
	PhysicsBody *physicsBody = PhysicsBody::createBox(this->getBoundingBox().size);
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0b00000001);
	this->setPhysicsBody(physicsBody);
}
