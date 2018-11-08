#include "ObjectFactory.h"
#include "TextureFactory.h"

template <class T>
T *ObjectFactory::create() {
	T *pObj = new T();
	if (pObj && pObj->initWithSpriteFrame(TextureFactory::getInstance().getEnemyTankSprite()))
	{
		pObj->autorelease();
		pObj->initObject();
		return pObj;
	}

	CC_SAFE_DELETE(pObj);
	return NULL;
}
