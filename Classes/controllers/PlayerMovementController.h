#pragma once
#ifndef __PLAYER_MOVEMENT_CONTROLLER_H__
#include "Player.h"

class PlayerMovementController
{
private:
	static PlayerMovementController* _instance;
	PlayerMovementController() {};
	Player* _player;
	int _movementDirection;
public:
	static PlayerMovementController* GetInstance();
	void InitializePlayerController();
	void update(float dt);
	void MovePlayer(float speed);
	void SetMovementDirection(int direction);
	void SetPlayer(Player* player) { _player = player; };
	Player* GetPlayer() { return _player; };
};

#endif //  __PLAYER_MOVEMENT_CONTROLLER_H__



