#pragma once

#include <array>
#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

class Tank : public Sprite {
public:

	void update(float dt);

	void moveTo(eDirection direct);
	void moveTo(eDirection direct, int delta);
	void stop();

	virtual ~Tank();
	void setNearbyObj(eDirection direction, ObjType objType);
	std::string printNearbyObj() {
		std::ostringstream stringStream;
		stringStream << "[";
		stringStream << "]";
		return stringStream.str();
	}
protected:
	int nX_delta;
	int nY_delta;
	Size winSize;//пока как костыль для убыстрения работы update(), но как-то не красиво сделано
	int width;
	int height;
	float life = 100.f;
	float damage_koef = .75f;
	int posX;
	int posY;

	eDirection direction;
	Animate *pMoveAnimate;
	std::array<ObjType, 4> nearbyObj;
	uint8_t posiblePos; //bitmask

	void initTank();
	void initPhysics();
	virtual void playAnimation();
	virtual void pauseAnimation();
	bool checkMoveToPosition(eDirection dir);
};
