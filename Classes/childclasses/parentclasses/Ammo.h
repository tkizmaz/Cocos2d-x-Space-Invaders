#pragma once
#ifndef __AMMO_H__
#include "SpriteCreator.h"
#include "cocos2d.h"
#include "Definitions.h"
#include "Player.h"

class Ammo : public SpriteCreator
{
private:
	int _damage;
	Sprite* _ammoSprite;
	int _ammoType;
public:
	Sprite* GetAmmoSprite() { return SpriteCreator::_shipSprite; };
	Ammo(int damage, std::string path, int ammoType, int _spriteWidth, int _spriteHeight);
	int GetAmmoDamage() { return _damage; };
	int GetAmmoType() { return _ammoType; };
};

#endif //  __AMMO_H__



