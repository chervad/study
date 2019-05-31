#include "Ground.h"

void Ground::initObject() {
}

void Ground::initPhysics() {
    Size size = this->getBoundingBox().size;
    PhysicsBody *physicsBody = PhysicsBody::createBox(size);
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(ObjType::GROUND);
    this->setPhysicsBody(physicsBody);
}
