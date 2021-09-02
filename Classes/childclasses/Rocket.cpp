#include "Rocket.h"

USING_NS_CC;

//Declaring rocket by calling parent class constructor with spesifict parameters to rocket
Rocket::Rocket() : Ammo(ROCKET_DAMAGE,ROCKET_PATH, ROCKET_TYPE_TAG, ROCKET_WIDTH,ROCKET_HEIGHT)
{

}
