#include "ObjectPoolManager.h"

USING_NS_CC;

///This class deals with pooling, returns and gets object from spesific pools

ObjectPoolManager* ObjectPoolManager::_instance = nullptr;

ObjectPoolManager* ObjectPoolManager::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new ObjectPoolManager;
	}


	return _instance;
}



void ObjectPoolManager::ReturnAmmoToPool(Ammo* ammo)
{
	//Removing it from scene
	_gameScene->removeChild(ammo);
	//Checking ammo type by getting and comparing
	if (ammo->GetAmmoType() == BULLET_TYPE_TAG) {
		//If it is bullet, return it to bullet pool
		_bulletPool.ReturnObjectToPool((Bullet*)ammo);
	}

	else {
		//If it is rocket, return it to bullet pool
		_rocketPool.ReturnObjectToPool((Rocket*)ammo);
	}
}

//To return enemies to pool
void ObjectPoolManager::ReturnEnemyShipsToPool(EnemyShip* enemyShip) {

	//Removing it from scene
	_gameScene->removeChild(enemyShip);
	//Reseting the ship
	enemyShip->ResetEnemyShip();

	//Checking enemyship type by getting and comparing
	if (enemyShip->GetEnemyType() == SMALL_SHIP_TYPE_TAG) {
		//If it is smallship, return it to smallship
		_smallShipPool.ReturnObjectToPool((SmallShip*)enemyShip);
	}

	else {
		////If it is largeship, return it to largeship
		_largeShipPool.ReturnObjectToPool((LargeShip*)enemyShip);
	}
}

//Checking parameter, if the type tag is bullet, get one bullet from pool, else get one from rocket pool
Ammo* ObjectPoolManager::GetAmmoFromPool(int ammoTag)
{
	if (ammoTag == BULLET_TYPE_TAG) {
		return _bulletPool.GetObjectFromPool();
	}

	return _rocketPool.GetObjectFromPool();

}

//Checking parameter, if the type tag is small ship, get one small ship from pool, else get one from large ship pool
EnemyShip* ObjectPoolManager::GetEnemyShipFromPool(int enemyTag)
{
	if (enemyTag == SMALL_SHIP_TYPE_TAG) {
		return _smallShipPool.GetObjectFromPool();
	}

	return _largeShipPool.GetObjectFromPool();
}

