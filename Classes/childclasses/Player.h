#pragma once
#ifndef __PLAYER_H__
#include "cocos2d.h"
#include "SpriteCreator.h"

class Player : public SpriteCreator
{
public:
	Player();
	Sprite* GetPlayerSprite() { return SpriteCreator::_shipSprite; };
};

#endif //  __PLAYER_H__



