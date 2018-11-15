#pragma once

#include "cocos2d.h"

#include "defens.h"

#include "TextureFactory.h"

using namespace cocos2d;

class GameObject : public Sprite {
public:
	template <class T> static T *create() {
		T *pObj = new T();
		if (pObj && pObj->initWithSpriteFrame(TextureFactory::getInstance().getSprite(pObj->getObjectType())))
		{
			pObj->autorelease();
			pObj->initObject();
			return pObj;
		}

		CC_SAFE_DELETE(pObj);
		return NULL;
	}

	virtual ~GameObject() {}

	virtual ObjType getObjectType() = 0;
protected:
	virtual void initObject() = 0;
};
