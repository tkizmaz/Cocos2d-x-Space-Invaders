#include "SmallShip.h"
#include "Definitions.h"
USING_NS_CC;

//Declaring smallship by calling parent class constructor with spesifict parameters to smallship
SmallShip::SmallShip() : EnemyShip(SMALL_SHIP_HEALTH, SMALL_SHIP_PATH, SMALL_SHIP_TYPE_TAG, SMALL_SHIP_WIDTH, SMALL_SHIP_HEIGHT)
{

}
