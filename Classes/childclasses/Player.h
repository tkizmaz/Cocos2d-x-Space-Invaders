#pragma once
#ifndef __PLAYER_H__
#include "cocos2d.h"
#include "SpriteCreator.h"
#include "Definitions.h"

//Forward declaring AmmoController to break circular dependency
class AmmoController;
class Player : public SpriteCreator
{
	AmmoController* _ammoController;
public:
	Player();
	Sprite* GetPlayerSprite() { return SpriteCreator::_shipSprite; };
	void FireAmmo(cocos2d::Scene* gameScene, bool _isRocketTurn);
	
};

#endif //  __PLAYER_H__



