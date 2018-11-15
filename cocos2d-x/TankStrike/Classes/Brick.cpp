#include "Brick.h"

#include "BattleLayer.h"

Brick *Brick::create(uint8_t lifes, uint16_t x, uint16_t y)
{
	Brick *pBrick = new Brick();
	if (pBrick && pBrick->initWithSpriteFrame(TextureFactory::getInstance().getBricks()[4 - lifes]))
	{
		pBrick->autorelease();
		pBrick->initObject();
		pBrick->lifes = lifes;
		pBrick->x = x;
		pBrick->y = y;
		return pBrick;
	}

	CC_SAFE_DELETE(pBrick);
	return NULL;
}

void Brick::initObject() {
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
			Brick *pBrick = Brick::create(this->lifes, this->x, this->y);
			Vec2 pos = this->getPosition();
			pBrick->setPosition(EnemyTank::convertArea2Pos(this->x, this->y));
			BattleLayer *parent = (BattleLayer *)(this->getParent());
			parent->addChild(pBrick);
			parent->set(pBrick);
		}
		else {
			log("Bricks destroyed!");
		}
		this->removeFromParent();
		this->release();
	}
}
