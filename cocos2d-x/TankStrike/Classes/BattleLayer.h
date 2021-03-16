#pragma once
#include <mutex>

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

	void addShot(Shot *pShot);
	void addEnemyTank(EnemyTank *pEnemyTank);
	void addEnemyBase(Vec2 position);

	CREATE_FUNC(BattleLayer);
private:
	PlayerTank *pPlayerTank;
	Maze *pMaze;

	float dt;
	float tileWidth;
	float tileHeight;

	std::list<Shot *> listShots;
	std::list<EnemyTank *>listEnemyTanks;
	std::list<Vec2> enemyBase;

	std::mutex guard_mutex;

public:
    /*
    PlayerTank *getPlayerTank() const;
    void onContactSeparate(PhysicsContact& contact);
	bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve);

	virtual void update(float dt);
     */
};
