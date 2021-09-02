#pragma once
#ifndef __AMMO_CONTROLLER_H__
#include "cocos2d.h"
#include "Ammo.h"
#include "Bullet.h"
#include "Rocket.h"
#include "Definitions.h"
#include "ObjectPoolManager.h"
#include "AudioEngine.h"

class AmmoController
{
private:
	static AmmoController* _instance;
	AmmoController() {};
	std::list<Ammo*> _allAmmoList;
public:
	static AmmoController* GetInstance();
	void InitializeAmmo(int positionX, int positionY, cocos2d::Scene* gameScene, bool _isRocketTurn);
	void MoveAmmos(float dt);
	void ReturnAmmoToList(Ammo* ammo) { _allAmmoList.remove(ammo); };
	void ResetAmmoController();
};

#endif //  __AMMO_CONTROLLER_H__



