#pragma once
#ifndef __GAME_MANAGER__
#include "cocos2d.h"
#include "Player.h"
#include "ObjectPool.h"
#include "SmallShip.h"
#include "LargeShip.h"
#include "Bullet.h"
#include "Rocket.h"
#include "Definitions.h";
#include "PlayerMovementController.h"
#include "EnemyShipController.h"
#include "ObjectPoolManager.h"
#include "AudioEngine.h"
class GameManager {

private:
	GameManager() {};
	cocos2d::Scene* _gameScene;
	static GameManager* _instance;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	Player* _player;
	std::list<Ammo*> allAmmoList;
	int _scoreToSwitchRocket = 0;
	bool _isRocketTurn;
	int _score = 0;
	float time = 0;
	float ammoTimer = 0;
	cocos2d::Label* scoreLabel;
	cocos2d::Label* switchedToRocketLabel;

public:

	cocos2d::Scene* GetScene() { return _gameScene; };
	static GameManager* GetInstance();
	void InitializeGame();
	void SetScene(cocos2d::Scene* scene) { _gameScene = scene; };
	void InitializeAmmos();
	void RemoveAmmoFromList(Ammo* ammo) {allAmmoList.remove(ammo)};
	void MoveBullets(float dt);
	void IncrementScore();
	void CheckAmmoSwitch();
	bool GetIsRocketTurn() { return _isRocketTurn; };
	void GameLoop(float dt);
	void GameOver();
	void SetIsRocketTurn(bool isRocketTurn) { _isRocketTurn = isRocketTurn; };
	void ResetSwitchScore() { _scoreToSwitchRocket = 0; };
	void ResetRound();
	void ReturnFinishedObjects();

};

#endif __GAME_MANAGER__
