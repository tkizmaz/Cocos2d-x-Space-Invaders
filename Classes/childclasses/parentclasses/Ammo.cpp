#include "Ammo.h"

USING_NS_CC;

///This class is parent class for both Bullet and Rocket classes.
///Type, damage and other parameters will be declared by its sublcasses


//Ammo takes damage, path, type, sprite width and height by its subclasses
Ammo::Ammo(int damage, std::string path, int ammoType, int _spriteWidth, int _spriteHeight) : SpriteCreator(path, _spriteWidth, _spriteHeight)
{
	//Setting tag, damage and type of Ammo object, will be determined by subclasses.
	this->setTag(AMMO_TAG);
	this->_damage = damage;
	this->_ammoType = ammoType;
}


