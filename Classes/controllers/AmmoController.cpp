#include "AmmoController.h"

USING_NS_CC;

//This class for creating and moving ammos

//Singleton class initalizations
AmmoController* AmmoController::_instance = nullptr;

AmmoController* AmmoController::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new AmmoController;
	}


	return _instance;
}

//To initialize ammos
void AmmoController::InitializeAmmo(int positionX, int positionY, cocos2d::Scene* gameScene, bool _isRocketTurn)
{
	Ammo* createdAmmo;
	AudioEngine::play2d(LASER_SHOT_SOUND_PATH);
	//If it is rocket turn 
	if (_isRocketTurn) {
		//Get rocket from rocket pool
		createdAmmo = ObjectPoolManager::GetInstance()->GetAmmoFromPool(ROCKET_TYPE_TAG);
	}

	else {
		//Get bullet from rocket pool
		createdAmmo = ObjectPoolManager::GetInstance()->GetAmmoFromPool(BULLET_TYPE_TAG);

	}
	//Setting position to top of the player
	createdAmmo->setPosition(Point(positionX, positionY + createdAmmo->getContentSize().height));

	//Adding to scene
	gameScene->addChild(createdAmmo, 1);

	//Firing created ammo
	_allAmmoList.push_back(createdAmmo);
}

//To move created enemies
void AmmoController::MoveAmmos(float dt) {
	//Creating iterator to iterate the list of created ships
	std::list<Ammo*>::iterator it;
	for (it = _allAmmoList.begin(); it != _allAmmoList.end(); ++it) {
		Ammo* eachBullet = *it;

		//If it is not null, set position smoothly to bottom of the screen
		if (eachBullet != nullptr) {
			eachBullet->setPositionY(eachBullet->getPosition().y + dt);
		}
	}
}


//Reseting singleton class to prevent left informations in previous scene
void AmmoController::ResetAmmoController()
{
	_instance = nullptr;
}
