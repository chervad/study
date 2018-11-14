#pragma once

#include "cocos2d.h"

#include "defens.h"

#include "GameObject.h"

using namespace cocos2d;

class Ground : public GameObject {
	friend class GameObject;
public:
	~Ground() {}

	virtual ObjType getObjectType() {
		return ObjType::GROUND;
	}
protected:
	void initObject();
};
