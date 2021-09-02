#pragma once
#ifndef __ENEMY_SHIP_CONTROLLER_H__
#include "cocos2d.h"
#include "EnemyShip.h"
#include "SmallShip.h"
#include "LargeShip.h"
#include "Definitions.h"
#include "ObjectPoolManager.h"

class EnemyShipController
{
private:
	static EnemyShipController* _instance;
	EnemyShipController() {};
	std::list<EnemyShip*> allEnemyShipList;
	cocos2d::Scene* _gameScene;
public:
	void SetScene(cocos2d::Scene* scene) { _gameScene = scene; };
	static EnemyShipController* GetInstance();
	void InitializeEnemies();
	void MoveEnemyShips(float dt);
	void ResetEnemies();
	void ResetEnemyShipController();
};

#endif //  __ENEMY_SHIP_CONTROLLER_H__



