#include "Bullet.h"

USING_NS_CC;

//Giving parameters to Ammo class constructor to specify this is Bullet object 
Bullet::Bullet() : Ammo(BULLET_DAMAGE,BULLET_PATH,BULLET_TYPE_TAG, BULLET_WIDTH,BULLET_HEIGHT)
{
	
}
