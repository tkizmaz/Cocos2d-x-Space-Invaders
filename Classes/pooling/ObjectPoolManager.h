#pragma once
#ifndef __OBJECT_POOL_MANAGER_H__
#include "cocos2d.h"
#include "Ammo.h"
#include "Bullet.h"
#include "Rocket.h"
#include "ObjectPool.h"
#include "Definitions.h"
#include "EnemyShip.h"
#include "SmallShip.h"
#include "LargeShip.h"

class ObjectPoolManager
{
private:
	static ObjectPoolManager* _instance;
	ObjectPoolManager() {};
	ObjectPool<Bullet> _bulletPool;
	ObjectPool<Rocket> _rocketPool;
	ObjectPool<SmallShip> _smallShipPool;
	ObjectPool<LargeShip> _largeShipPool;
	cocos2d::Scene* _gameScene;
public:
	void SetScene(cocos2d::Scene* scene) { _gameScene = scene; };
	static ObjectPoolManager* GetInstance();
	void ReturnAmmoToPool(Ammo* ammo);
	void ReturnEnemyShipsToPool(EnemyShip* enemyShip);
	Ammo* GetAmmoFromPool(int ammoTag);
	EnemyShip* GetEnemyShipFromPool(int enemyTag);
};

#endif __OBJECT_POOL_MANAGER_H__



