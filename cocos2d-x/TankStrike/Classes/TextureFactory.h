#pragma once

#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

typedef std::tuple<uint8_t, uint8_t> tiletype;

class TextureFactory {
public:
	static TextureFactory &getInstance();

	SpriteFrame *getHeroTankSprite();
	SpriteFrame *getEnemyTankSprite();
private:
	TextureFactory();
	TextureFactory(const TextureFactory&) {}
	TextureFactory& operator=(const TextureFactory&) {}
private:
	const char *tiles_res = "res/sprites/tiles.png";
	const tiletype heroTankTile = { 14, 0 };
	const tiletype enemyTankTile = { 17, 4 };

	Texture2D *pTextures;

	SpriteFrame *pHeroTank;
	SpriteFrame *pEnemyTank;

	float tileWidth;
	float tileHeight;
};
