#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

//Splash scene display and the time for transition
#define DISPLAY_TIME_SPLASH_SCENE 2
#define TRANSITION_TIME 1

//Paths for sprites
#define LARGE_SHIP_PATH "sprites/largeship.png"
#define SMALL_SHIP_PATH "sprites/smallship.png"
#define PLAYER_SHIP_PATH "sprites/playership.png"
#define ROCKET_PATH "sprites/rocket.png"
#define BULLET_PATH "sprites/bullet.png"

//Healths of ships 
#define LARGE_SHIP_HEALTH 100
#define SMALL_SHIP_HEALTH 50

//Damage for ammos, different type has different damage
#define BULLET_DAMAGE 25
#define ROCKET_DAMAGE 100

//Tags to declare type for objects
#define ENEMY_SHIP_TAG 99
#define PLAYER_TAG 100
#define AMMO_TAG 101

//Type tags to differentiate child classes
#define LARGE_SHIP_TYPE_TAG 102
#define SMALL_SHIP_TYPE_TAG 103
#define BULLET_TYPE_TAG 104
#define ROCKET_TYPE_TAG 105

//Sprite sizes
#define SHIP_HEIGHT 50
#define SHIP_WIDTH 50
#define BULLET_HEIGHT 17
#define BULLET_WIDTH 3
#define ROCKET_HEIGHT 16
#define ROCKET_WIDTH 10
#define LARGE_SHIP_HEIGHT 11
#define LARGE_SHIP_WIDTH 15
#define SMALL_SHIP_HEIGHT 11 
#define SMALL_SHIP_WIDTH 15
#define PLAYER_SHIP_HEIGHT 30
#define PLAYER_SHIP_WIDTH 25

//Rocket duration
#define AMMO_DURATION 3

//Enemy count
#define ENEMY_COUNT 30

//sound paths
#define LASER_SHOT_SOUND_PATH "sounds/laser_shot.mp3"
#define SHIP_EXPLOSION_PATH "sounds/ship_explosion.mp3"

#endif // __DEFINITIONS_H__
