#pragma once
#ifndef __SPRITE_CREATOR__
#include "cocos2d.h"
#include <string>
class SpriteCreator : public cocos2d::Sprite {

public:
	SpriteCreator(std::string spritePath, float width, float height);
	cocos2d::Sprite* _shipSprite;
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

};

#endif // __SPRITE_CREATOR__
