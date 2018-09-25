#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class BattleScene : public Layer
{
public:
	BattleScene(); 

	virtual ~BattleScene();

    static Scene* createScene();

    virtual bool init();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);

	virtual void update(float dt);

	CREATE_FUNC(BattleScene);
private:
	void fillAnimatation(Animation *animation);
private:
	Texture2D *pTextures;
	Sprite *pTankHero;
	Animate *pTankHeroMove;
	Sprite *pTank;
	bool createAnimate;
	int nX_delta;
	int nY_delta;
	float dt;
	float tileWidth;
	float tileHeight;
};

#endif // __HELLOWORLD_SCENE_H__