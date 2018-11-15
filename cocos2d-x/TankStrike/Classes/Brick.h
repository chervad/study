#pragma once

#include "cocos2d.h"

#include "defens.h"

#include "GameObject.h"

using namespace cocos2d;

class Brick : public GameObject {
	friend class GameObject;
public:
	~Brick() {};

	static Brick *create() = delete;
	static Brick *create(uint8_t lifes, uint16_t x, uint16_t y);

	virtual ObjType getObjectType() {
		return ObjType::BRICK;
	}

	void Blast();
protected:
	void initObject();
	void initPhysics();

	uint16_t x;
	uint16_t y;
	uint8_t lifes;
};
