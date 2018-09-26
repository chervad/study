#pragma once

#include "cocos2d.h"

#include "defens.h"

using namespace cocos2d;

typedef std::tuple<uint8_t, uint8_t> tiletype;

class TextureFactory {
public:
	static TextureFactory &getInstance();

	SpriteFrame *getPlayerTankSprite();
	Animate *getPlayerTankAnimate();
	SpriteFrame *getEnemyTankSprite();
private:
	TextureFactory();
	TextureFactory(const TextureFactory&) {}
	TextureFactory& operator=(const TextureFactory&) {}
private:
	const char *tiles_res = "res/sprites/tiles.png";
	const tiletype playerTankTile = { 14, 0 };
	const tiletype enemyTankTile = { 17, 4 };

	Texture2D *pTextures;

	SpriteFrame *pPlayerTank;
	SpriteFrame *pEnemyTank;

	Animate *pPlayerTankAnimate;

	float tileWidth;
	float tileHeight;
};
