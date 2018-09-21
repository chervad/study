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

    CREATE_FUNC(HelloWorld);

	virtual void update(float dt);

protected:

	void runAnimation();

private:
	Sprite *pTankHero;
	RepeatForever *pAnimateMoveTrucks;
	int nX_delta;
	int nY_delta;
	u_short nCountKeyPressed;
	float dt;
};

#endif // __HELLOWORLD_SCENE_H__
