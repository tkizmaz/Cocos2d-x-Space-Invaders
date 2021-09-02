#include "GameManager.h"
#include "MainMenuScene.h"
USING_NS_CC;

//For singleton initializations.
GameManager* GameManager::_instance = nullptr;

GameManager* GameManager::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new GameManager;
	}


	return _instance;
}

//At the start of the game, initializing variables
void GameManager::InitializeGame()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	//Setting player from getting it from controller
	_player = PlayerMovementController::GetInstance()->GetPlayer();

	//Setting position to center on x axis and bottom of the scene
	_player->setPosition(Point(visibleSize.width / 2 + SHIP_WIDTH, origin.y + SHIP_HEIGHT));

	//Adding player to scene
	_gameScene->addChild(_player,1);

	//To initialize enemies
	EnemyShipController::GetInstance()->InitializeEnemies();

	//Creating label and placing it to left of the screen, the label returns "SCORE: "
	auto scoreIsLabel = Label::createWithTTF("SCORE: ", "fonts/arial.ttf", 15);
	scoreIsLabel->setPosition(Point(origin.x + scoreIsLabel->getContentSize().width, visibleSize.height - scoreIsLabel->getContentSize().height));
	_gameScene->addChild(scoreIsLabel, 1000);

	//Label to display score and place
	scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 15);
	scoreLabel->setPosition(Point(origin.x + scoreLabel->getContentSize().width + scoreIsLabel->getPositionX(), visibleSize.height - scoreLabel->getContentSize().height));
	_gameScene->addChild(scoreLabel, 1000);

	//If it is turn to switch to rockets, show player it is rocket time
	switchedToRocketLabel = Label::createWithTTF("STREAK! Switched to Rocket!", "fonts/arial.ttf", 15);
	switchedToRocketLabel->setPosition(Point(visibleSize.width/2 + scoreIsLabel->getContentSize().width, visibleSize.height - switchedToRocketLabel->getContentSize().height));
	_gameScene->addChild(switchedToRocketLabel);
	switchedToRocketLabel->setVisible(false);
	//To check the rocket turn time, initially false
	_isRocketTurn = false;

}



//To initialize Ammos
void GameManager::InitializeAmmos()
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
	createdAmmo->setPosition(Point(_player->getPosition().x, _player->getPosition().y + createdAmmo->getContentSize().height + 10));

	//Adding to scene
	_gameScene->addChild(createdAmmo, 1);

	//Firing created ammo
	allAmmoList.push_back(createdAmmo);

}


void GameManager::IncrementScore()
{
	//Main score

	//This score is for reseting, when 5 score is achieved it resets to switch to rocket
	_scoreToSwitchRocket++;
	_score = std::atoi(scoreLabel->getString().c_str());;
	_score++;
	scoreLabel->setString(StringUtils::format("%d", _score));
}


//Stopping all actions
void GameManager::GameOver()
{
	//Reseting singleton classes to prevent the informations from previous scene
	_instance = nullptr;
	EnemyShipController::GetInstance()->ResetEnemyShipController();
	//Creating main menu scene
	auto scene = MainMenuScene::createScene();

	//Changing scene with Fade transition and the time declared
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));



}


//Checking if ammo switch available
void GameManager::CheckAmmoSwitch()
{
	//If score achieved to 5, it is rocket turn
	if (_scoreToSwitchRocket == 5) {
		_isRocketTurn = true;
	}
}



//Reseting round, if there is no enemy ship, clear the list and initialize new enemies
void GameManager::ResetRound() {

	if (_gameScene->getChildByTag(ENEMY_SHIP_TAG) == 0) {
		EnemyShipController::GetInstance()->ResetEnemies();
	}
}

//Game loop is for update function, check everytime
void GameManager::GameLoop(float dt) {
	ammoTimer += dt;
	if (ammoTimer >= AMMO_FREQUENCY) {
		InitializeAmmos();
		ammoTimer = 0;
	}
	//Moving ships
	EnemyShipController::GetInstance()->MoveEnemyShips(dt / Director::getInstance()->getAnimationInterval() * SHIP_MOVE_SPEED);
	//Checking if there is ship left
	ResetRound();
	//Checking if switch to rocket is available
	CheckAmmoSwitch();
	//Moving bullets
	MoveBullets(dt / Director::getInstance()->getAnimationInterval() * BULLET_MOVE_SPEED);
	//Checking and returning done but not returned to pool objects
	ReturnFinishedObjects();
	//If it is rocket turn calculate time for 3 seconds, after 3 seconds return to bullets
	if (GetIsRocketTurn()) {
		switchedToRocketLabel->setVisible(true);
		time += dt;
		if (time >= 3) {
			switchedToRocketLabel->setVisible(false);
			SetIsRocketTurn(false);
			ResetSwitchScore();
			time = 0;
		}
	}

}

//To move created enemies
void GameManager::MoveBullets(float dt) {
	//Creating iterator to iterate the list of created ships
	std::list<Ammo*>::iterator it;
	for (it = allAmmoList.begin(); it != allAmmoList.end(); ++it) {
		Ammo* eachBullet = *it;

		//If it is not null, set position smoothly to bottom of the screen
		if (eachBullet != nullptr) {
			eachBullet->setPositionY(eachBullet->getPosition().y + dt);
		}
	}
}

//Checking if objects are done but not returned, for example if a bullet did not hit a ship and gone to top of the screen, it should also be returned
void GameManager::ReturnFinishedObjects() {
	cocos2d::Vector<Node*> allObjects = _gameScene->getChildren();
	for each (Node * child in allObjects) {
		if (child->getTag() == AMMO_TAG) {
			Ammo* finishedAmmo = (Ammo*)child;
			//Checking if ammo go above the screen
			if (finishedAmmo->getPositionY() >= origin.y + visibleSize.height + 10.f) {
				_gameScene->removeChild(finishedAmmo);
				RemoveAmmoFromList(finishedAmmo);
				ObjectPoolManager::GetInstance()->ReturnAmmoToPool(finishedAmmo);
			}
		}

		else if (child->getTag() == ENEMY_SHIP_TAG) {
			EnemyShip* finishedEnemy = (EnemyShip*)child;
			//Checking if enemies reached to bottom of screen
			if (finishedEnemy->getPositionY() <= origin.y) {
				//Return them back to pool
				ObjectPoolManager::GetInstance()->ReturnEnemyShipsToPool(finishedEnemy);

			}
		}
	}
}
