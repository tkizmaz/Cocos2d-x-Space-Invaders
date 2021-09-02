#include "EnemyShip.h"

USING_NS_CC;

//Enemyship constructor takes health, path, tag, width and height by its subclasses.
EnemyShip::EnemyShip(int enemyShipHealth, std::string spritePath, int enemyTag, int _spriteWidth, int _spriteHeight) : SpriteCreator::SpriteCreator(spritePath, _spriteWidth, _spriteHeight)
{
	//Setting paramaters given by subclasses
	this->_enemyTag = enemyTag;
	this->_enemyShipHealth = enemyShipHealth;
	this->_isDead = false;
	//Setting tag
	this->setTag(ENEMY_SHIP_TAG);
	//Holding constant health, when it returned by pool, health should be reset
	this->constantHealth = enemyShipHealth;
}

//Take damage function takes ammo and decreasing health by ammos's damage
void EnemyShip::TakeDamage(Ammo* ammo)
{
	this->_enemyShipHealth -= ammo->GetAmmoDamage();
	//Checking if it is dead
	CheckIsDead();
}

//Checking if health is 0 or less
bool EnemyShip::CheckIsDead()
{
	return this->_enemyShipHealth <= 0;

}

//Reseting ship for returning from pool
void EnemyShip::ResetEnemyShip()
{
	this->_enemyShipHealth = constantHealth;
}



