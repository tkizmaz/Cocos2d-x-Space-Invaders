#include "SpriteCreator.h"

USING_NS_CC;

SpriteCreator::SpriteCreator(std::string spritePath, float width, float height) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Creating sprite from the file

	//Initializing sprite from path
	if (!Sprite::initWithFile(spritePath))
	{
		return;
	}

	setContentSize(cocos2d::Size(width, height));
	//Creating body for player
	auto _playerShipBody = PhysicsBody::createBox(this->getContentSize(),PHYSICSBODY_MATERIAL_DEFAULT);
	_playerShipBody->setContactTestBitmask(true);

	//Adding body to sprite
	this->setPhysicsBody(_playerShipBody);


}