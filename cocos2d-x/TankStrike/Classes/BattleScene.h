#pragma once

#include "cocos2d.h"

#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Wall.h"

using namespace cocos2d;

class BattleScene : public Layer
{
public:
	BattleScene(); 
	~BattleScene();

    static Scene* createScene();

    virtual bool init();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);

	virtual void update(float dt);

	CREATE_FUNC(BattleScene);
private:
	PlayerTank *pPlayerTank;
	EnemyTank *pEnemyTank;
	Wall *pWall;

	float dt;
	float tileWidth;
	float tileHeight;
};
