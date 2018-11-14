#pragma once

#include "cocos2d.h"

#include "defens.h"

#include "GameObject.h"

using namespace cocos2d;

class Eagle : public GameObject {
	friend class GameObject;
public:
	~Eagle() {}

	virtual ObjType getObjectType() {
		return ObjType::EAGLE;
	}
protected:
	void initObject();
};
