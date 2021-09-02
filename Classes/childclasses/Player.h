#pragma once
#ifndef __PLAYER_H__
#include "cocos2d.h"
#include "SpriteCreator.h"
#include "AmmoController.h"

class Player : public SpriteCreator
{
public:
	Player();
	Sprite* GetPlayerSprite() { return SpriteCreator::_shipSprite; };
	void FireAmmo(cocos2d::Scene* _gameScene, bool isRocketTurn);
};

#endif //  __PLAYER_H__



