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

	_ammoController = AmmoController::GetInstance();

	//Creating label and placing it to left of the screen, the label returns "SCORE: "
	auto scoreIsLabel = Label::createWithTTF("SCORE: ", "fonts/arial.ttf", 15);
	scoreIsLabel->setPosition(Point(origin.x + scoreIsLabel->getContentSize().width, visibleSize.height - scoreIsLabel->getContentSize().height));
	_gameScene->addChild(scoreIsLabel, 1000);

	//Label to display score and place
	_scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 15);
	_scoreLabel->setPosition(Point(origin.x + _scoreLabel->getContentSize().width + scoreIsLabel->getPositionX(), visibleSize.height - _scoreLabel->getContentSize().height));
	_gameScene->addChild(_scoreLabel, 1000);

	//If it is turn to switch to rockets, show player it is rocket time
	_switchedToRocketLabel = Label::createWithTTF("STREAK! Switched to Rocket!", "fonts/arial.ttf", 15);
	_switchedToRocketLabel->setPosition(Point(visibleSize.width/2 + scoreIsLabel->getContentSize().width, visibleSize.height - _switchedToRocketLabel->getContentSize().height));
	_gameScene->addChild(_switchedToRocketLabel);
	_switchedToRocketLabel->setVisible(false);
	//To check the rocket turn time, initially false
	_isRocketTurn = false;

}


void GameManager::IncrementScore()
{
	//Main score

	//This score is for reseting, when 5 score is achieved it resets to switch to rocket
	_scoreToSwitchRocket++;
	_score = std::atoi(_scoreLabel->getString().c_str());;
	_score++;
	_scoreLabel->setString(StringUtils::format("%d", _score));
}


//Stopping all actions
void GameManager::GameOver()
{
	//Reseting singleton classes to prevent the informations from previous scene
	_instance = nullptr;
	EnemyShipController::GetInstance()->ResetEnemyShipController();
	_ammoController->ResetAmmoController();
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
	_ammoTimer += dt;
	if (_ammoTimer >= AMMO_FREQUENCY) {
		_ammoController->InitializeAmmo(_player->getPosition().x, _player->getPosition().y + 10, _gameScene, _isRocketTurn);
		_ammoTimer = 0;
	}
	//Moving ships
	EnemyShipController::GetInstance()->MoveEnemyShips(dt / Director::getInstance()->getAnimationInterval() * SHIP_MOVE_SPEED);
	//Checking if there is ship left
	ResetRound();
	//Checking if switch to rocket is available
	CheckAmmoSwitch();
	//Moving bullets
	_ammoController->MoveAmmos(dt / Director::getInstance()->getAnimationInterval() * BULLET_MOVE_SPEED);
	//Checking and returning done but not returned to pool objects
	ReturnFinishedObjects();
	//If it is rocket turn calculate time for 3 seconds, after 3 seconds return to bullets
	if (GetIsRocketTurn()) {
		_switchedToRocketLabel->setVisible(true);
		_time += dt;
		if (_time >= 3) {
			_switchedToRocketLabel->setVisible(false);
			SetIsRocketTurn(false);
			ResetSwitchScore();
			_time = 0;
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
				_ammoController->ReturnAmmoToList(finishedAmmo);
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
