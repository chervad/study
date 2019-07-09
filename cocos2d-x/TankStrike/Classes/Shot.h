#pragma once

#include "cocos2d.h"

#include "defens.h"

#include "GameObject.h"

using namespace cocos2d;

class Shot : public GameObject {
	friend class GameObject;
public:
	virtual ~Shot();

	static Shot *create(eDirection direction, const Vec2 &position);

	virtual ObjType getObjectType() {
		return ObjType::SHOT;
	}

	void update(float dt);
	void Boom();
protected:
	bool isBoom;
	uint16_t damage = 20;
    eDirection direction;
	Animate *pBoomAnimate;

	void initObject();
	void initPhysics();
};
