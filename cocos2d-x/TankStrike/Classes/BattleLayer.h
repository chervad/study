#pragma once

#include "cocos2d.h"

#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Maze.h"
#include "Shot.h"
#include "Brick.h"

using namespace cocos2d;

class BattleLayer : public Layer
{
public:
	BattleLayer(); 
	~BattleLayer();

    static Scene* createScene();

    virtual bool init();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);
	bool onContactBegin(PhysicsContact &contact);

	virtual void update(float dt);

	void addShot(Shot *pShot);

	void set(Brick *br) {
		this->br = br;
	}

	CREATE_FUNC(BattleLayer);
private:
	PlayerTank *pPlayerTank;
	EnemyTank *pEnemyTank;
	Maze *pMaze;

	float dt;
	float tileWidth;
	float tileHeight;
	Brick *br;

	std::list<Shot *> listShots;
};
