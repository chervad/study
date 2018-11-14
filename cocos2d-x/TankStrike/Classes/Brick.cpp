#include "Brick.h"

void Brick::initObject() {
	this->initPhysics();
}

void Brick::initPhysics() {
	PhysicsBody *physicsBody = PhysicsBody::createBox(this->getBoundingBox().size);
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0b00000100);
	this->setPhysicsBody(physicsBody);
}