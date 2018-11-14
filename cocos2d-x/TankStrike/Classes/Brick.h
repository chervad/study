#pragma once

#include "cocos2d.h"

#include "defens.h"

#include "GameObject.h"

using namespace cocos2d;

class Brick : public GameObject {
	friend class GameObject;
public:
	~Brick() {}

	virtual ObjType getObjectType() {
		return ObjType::BRICK;
	}
protected:
	void initObject();
	void initPhysics();
};
