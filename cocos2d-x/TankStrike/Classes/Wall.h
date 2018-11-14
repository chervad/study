#pragma once

#include "cocos2d.h"

#include "defens.h"

#include "GameObject.h"

using namespace cocos2d;

class Wall : public GameObject {
	friend class GameObject;
public:
	~Wall() {}

	virtual ObjType getObjectType() {
		return ObjType::WALL;
	}
protected:
	void initObject();
	void initPhysics();
};
