#pragma once
#ifndef __PLAYER_H__
#include "cocos2d.h"
#include "SpriteCreator.h"
#include "AudioEngine.h"
#include "Definitions.h"

class Player : public SpriteCreator
{

public:
	Player();
	Sprite* GetPlayerSprite() { return SpriteCreator::_shipSprite; };
	void FireAmmo(cocos2d::Scene* gameScene, bool _isRocketTurn);
	
};

#endif //  __PLAYER_H__



