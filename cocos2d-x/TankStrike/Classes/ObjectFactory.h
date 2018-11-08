#pragma once

#include "cocos2d.h"

#include "defens.h"

#include "Wall.h"

using namespace cocos2d;

class ObjectFactory {
public:
	template <class T>
	static T *create();
};
