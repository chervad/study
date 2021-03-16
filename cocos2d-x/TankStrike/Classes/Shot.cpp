#include "Shot.h"

#define TX(X) std::get<0>(X)
#define TY(Y) std::get<1>(Y)
#define TILERECT(TILEDIFF, TILEWIDTH, TILEHEIGHT) Rect(TX(TILEDIFF) * TILEWIDTH, TY(TILEDIFF) * TILEHEIGHT, TILEWIDTH, TILEHEIGHT)

inline tiletype diff2tiletype(uint16_t d) {
	uint8_t x = d % TextureFactory::maxXTile;
	uint8_t y = d / TextureFactory::maxXTile;
	return std::tuple<uint8_t, uint8_t>(x, y);
}

Shot::~Shot()
{
	CC_SAFE_RELEASE(pBoomAnimate);
}

Shot *Shot::create(eDirection direction, const Vec2 &position)
{
	Shot *pShot = GameObject::create<Shot>();
	//pShot->retain();

	pShot->direction = direction;
	pShot->setPosition(position);

	//pShot->initObject();
	return pShot;
}

void Shot::initObject() {
	isBoom = false;
	pBoomAnimate = TextureFactory::getInstance().getAnimate(getObjectType());
	pBoomAnimate->retain();

	initPhysics();
}

void Shot::initPhysics() {
	Size size = this->getBoundingBox().size;
	size.width /= 3;
	size.height /= 3;
	PhysicsBody *physicsBody = PhysicsBody::createBox(size);
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(ObjType::SHOT);
	this->setPhysicsBody(physicsBody);
}

void Shot::update(float dt) {
	if (!isBoom) {
		Vec2 position = getPosition();
		switch (direction) {
		case eDirection::LEFT:
			position.x -= 4;
			break;
		case eDirection::RIGHT:
			position.x += 4;
			break;
		case eDirection::UP:
			position.y += 4;
			break;
		case eDirection::DOWN:
			position.y -= 4;
			break;
		}
		setPosition(position);
	}
}

void Shot::Boom() {
	isBoom = true;
	auto func = CallFunc::create([this]() {
		//this->pBoomAnimate->stop();
		this->stopAllActions();
		//this->pBoomAnimate->release();
		this->removeFromParent();
		this->release();
	});
	auto a = runAction(Sequence::create(pBoomAnimate, func, nullptr));
}
