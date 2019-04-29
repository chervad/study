#include "Shot.h"

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

	pBoomAnimate = TextureFactory::getInstance().getAnimate(getObjectType())->clone();
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
		this->pBoomAnimate->release();
		this->removeFromParent();
		this->release();
	});
	auto a = runAction(Sequence::create(pBoomAnimate, func, nullptr));
}
