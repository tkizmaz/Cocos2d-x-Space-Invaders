#include "PlayerMovementController.h"

PlayerMovementController* PlayerMovementController::_instance = nullptr;

PlayerMovementController* PlayerMovementController::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new PlayerMovementController;
	}


	return _instance;
}

//To call it every frame
void PlayerMovementController::update(float dt)
{
	MovePlayer(dt);
}

//Initializing the player as new
void PlayerMovementController::InitializePlayerController()
{
	_player = new Player;
}

//To move player, it takes direction and speed given by choice if direction comes negative it goes left else, right
void PlayerMovementController::MovePlayer(float speed)
{
	_player->setPositionX(_player->getPosition().x + (speed* _movementDirection));
}

//To set direction
void PlayerMovementController::SetMovementDirection(int direction)
{
	this->_movementDirection = direction;
}
