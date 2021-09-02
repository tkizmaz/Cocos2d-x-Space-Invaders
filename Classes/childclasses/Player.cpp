#include "Player.h"
#include "Definitions.h"
USING_NS_CC;

//Call sprite creator constructor by giving spesific parameters to player
Player::Player() : SpriteCreator(PLAYER_SHIP_PATH, PLAYER_SHIP_WIDTH,PLAYER_SHIP_HEIGHT)
{

	//Set tag of player
	setTag(PLAYER_TAG);
}

void Player::FireAmmo(cocos2d::Scene* _gameScene, bool isRocketTurn)
{
	AmmoController::GetInstance()->InitializeAmmo(this->getPosition().x, this->getPosition().y + 10,_gameScene,isRocketTurn);
}
