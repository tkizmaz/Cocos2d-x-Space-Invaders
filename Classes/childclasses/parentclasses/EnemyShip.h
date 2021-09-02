#pragma once
#ifndef __ENEMY_SHIP_H__
#include "SpriteCreator.h"
#include "cocos2d.h"
#include "Ammo.h"
#include "Definitions.h"
class EnemyShip : public SpriteCreator
{
public:
	EnemyShip(int enemyShipHealth, std::string spritePath, int enemyType, int _spriteWidth, int _spriteHeight);
	int GetHealth() { return this->_enemyShipHealth; };
	void TakeDamage(Ammo* ammo);
	bool CheckIsDead();
	int GetEnemyType() { return _enemyType; };
	void ResetEnemyShip();
private:
	int _enemyShipHealth;
	int _enemyTag;
	int _enemyType;
	bool _isDead;
	int constantHealth;
};

#endif //  __ENEMY_SHIP_H__



