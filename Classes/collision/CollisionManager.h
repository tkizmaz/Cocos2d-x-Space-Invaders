#ifndef __COLLISION_MANAGER__
#include "cocos2d.h"
#include "Player.h"
#include "GameManager.h"
#include <Definitions.h>
#include "ObjectPoolManager.h"
#include "EnemyShipController.h"
#include "AudioEngine.h"

class CollisionManager {

private:
	static CollisionManager* _instance;
public:
	static CollisionManager* GetInstance();
	CollisionManager() {};
	void EnemyPlayerCollision();
	void EnemyBulletCollision(EnemyShip* enemyShip, Ammo* ammo);
};

#endif // __COLLISION_MANAGER__
