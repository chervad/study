#include "Wall.h"

void Wall::initObject() {
	this->initPhysics();
}

void Wall::initPhysics() {
	PhysicsBody *physicsBody = PhysicsBody::createBox(this->getBoundingBox().size);
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(ObjType::WALL);
	this->setPhysicsBody(physicsBody);
}
