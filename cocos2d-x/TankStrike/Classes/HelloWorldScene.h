#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

#define DELTA 1

class HelloWorld : public Layer
{
public:
	HelloWorld(); 

	virtual ~HelloWorld();

    static Scene* createScene();

    virtual bool init();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);

	virtual void update(float dt);

	void loadObjects();

	CREATE_FUNC(HelloWorld);
private:
	void fillAnimatation(Animation *animation);
private:
	Texture2D *pTextures;
	Sprite *pTankHero;
	Animation *pTankHeroMoveAnimation;
	Sprite *pTank;
	bool createAnimate;
	int nX_delta;
	int nY_delta;
	float dt;
	float tileWidth;
	float tileHeight;
};

#endif // __HELLOWORLD_SCENE_H__
