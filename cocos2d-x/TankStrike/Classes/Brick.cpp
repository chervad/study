#include "Brick.h"

#include "Maze.h"

void Brick::initObject() {
	this->lifes = 4;
	this->initPhysics();
}

void Brick::initPhysics() {
	Size size = this->getBoundingBox().size;
	PhysicsBody *physicsBody = PhysicsBody::createBox(size);
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(ObjType::BRICK);
	this->setPhysicsBody(physicsBody);
}

void Brick::Blast() {
 	if (this->lifes > 0) {
		this->lifes--;
		if (lifes > 0) {
			setSpriteFrame(TextureFactory::getInstance().getBricks()[4 - lifes]);
		}
		else {
			Maze::setMazePlan(this->getPosition(), ' ');
			this->removeFromParent();
			this->release();
		}
	}
}
