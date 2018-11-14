#pragma once

#include "cocos2d.h"

#include "defens.h"

#include "GameObject.h"

using namespace cocos2d;

class Shot : public GameObject {
	friend class GameObject;
public:
	~Shot() {}

	static Shot *create(MoveDirection direction, const Vec2 &position);

	virtual ObjType getObjectType() {
		return ObjType::SHOT;
	}

	void update(float dt);
protected:
	MoveDirection eDirection;

	void initPhysics();
};
