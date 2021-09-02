#include "EnemyShipController.h"

USING_NS_CC;

//This class for creating and moving enemyships

//Singleton class initalizations
EnemyShipController* EnemyShipController::_instance = nullptr;

EnemyShipController* EnemyShipController::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new EnemyShipController;
	}


	return _instance;
}

//Initializing enemies
void EnemyShipController::InitializeEnemies()
{
	int previousObjectWidth = 0;
	int previousObjectHeight = 0;
	EnemyShip* createdEnemy;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Creating enemies by enemy count
	for (int i = 0; i < ENEMY_COUNT; i++) {
		//Getting random between 1 and 2
		int random = rand() % 2;

		//If random returns 1 create small ship
		if (random == 1) {
			//Getting small ship from pool
			createdEnemy = ObjectPoolManager::GetInstance()->GetEnemyShipFromPool(SMALL_SHIP_TYPE_TAG);
			
		}

		//If random returns 2
		else {
			//Getting large ship from pool
			createdEnemy = ObjectPoolManager::GetInstance()->GetEnemyShipFromPool(LARGE_SHIP_TYPE_TAG);
			
		}

		previousObjectWidth += createdEnemy->getContentSize().width + ROCKET_WIDTH;
		
		//Checking if a row finished, place them to new row
		if (visibleSize.width - previousObjectWidth < origin.x) {
			//Switching row to height of created object
			previousObjectHeight += createdEnemy->getContentSize().height;
			//Reseting width because it is new row
			previousObjectWidth = 0;
			//Adding width 
			previousObjectWidth += createdEnemy->getContentSize().width + ROCKET_WIDTH;
		}

		//Setting position of enemies and giving gap at the top of the scene with given row and column
		createdEnemy->setPosition(Point(visibleSize.width - previousObjectWidth, visibleSize.height - createdEnemy->getContentSize().height + previousObjectHeight));

		//Adding created smallship to scene
		_gameScene->addChild(createdEnemy, 1);
		allEnemyShipList.push_back(createdEnemy);
	}
}

//To move enemy ships
void EnemyShipController::MoveEnemyShips(float dt)
{
	//Creating iterator to iterate the list of created ships
	std::list<EnemyShip*>::iterator it;
	for (it = allEnemyShipList.begin(); it != allEnemyShipList.end(); ++it) {
		EnemyShip* eachEnemy = *it;

		//If it is not null, set position smoothly to bottom of the screen
		if (eachEnemy != nullptr) {
			eachEnemy->setPositionY(eachEnemy->getPosition().y - dt);
		}
	}
}

//To reset enemies, clearing the list of whole enemy list and initialize new ones
void EnemyShipController::ResetEnemies()
{
	allEnemyShipList.clear();
	InitializeEnemies();
}

//Reseting singleton class to prevent left informations in previous scene
void EnemyShipController::ResetEnemyShipController()
{
	_instance = nullptr;
}
