#include "CollisionManager.h"

///This class, designed from Singleton pattern handles collision types

USING_NS_CC;
//For singleton class initializatons
CollisionManager* CollisionManager::_instance = nullptr;
CollisionManager* CollisionManager::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new CollisionManager;
	}
	return _instance;
}

//To deal with enemy - player collisions
void CollisionManager::EnemyPlayerCollision()
{
	//Calling game over from GameManager
	GameManager::GetInstance()->GameOver();
}

//To deal with enemy - bullet collisions
void CollisionManager::EnemyBulletCollision(EnemyShip* enemyShip, Ammo* ammo)
{
	//Returning ammo to pool
	ObjectPoolManager::GetInstance()->ReturnAmmoToPool(ammo);
	//Returning ammo to manager to delete it from the list
	GameManager::GetInstance()->RemoveAmmoFromList(ammo);

	//Damaging enemyship by ammo's damage
	enemyShip->TakeDamage(ammo);

	//Checking if enemyship died
	if (enemyShip->CheckIsDead()) {
		//If dead, return ship to pool
		AudioEngine::play2d(SHIP_EXPLOSION_PATH);
		ObjectPoolManager::GetInstance()->ReturnEnemyShipsToPool(enemyShip);
		//Increment score
		GameManager::GetInstance()->IncrementScore();
	}
}
