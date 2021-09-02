/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "GameScene.h"
#include <string>
#include <windows.h>
#include "ui/CocosGUI.h"
#include "MainMenuScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();

    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    auto layer = GameScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    //Creating listeners for touches
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //At the beginning player can't move
    _isMoveable = false;

    //BACKGROUND SPRITE
    auto backGround = Sprite::create("sprites/background.png");
    backGround->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backGround);

    //To set player movement controller, collision manager and gamemanager singleton classes
    _playerMovementController = PlayerMovementController::GetInstance();
    _playerMovementController->InitializePlayerController();
    _enemyShipController = EnemyShipController::GetInstance();
    _enemyShipController->SetScene(this);
    _objectPoolManager = ObjectPoolManager::GetInstance();
    _objectPoolManager->SetScene(this);
    _collisionManager = CollisionManager::GetInstance();
    _gameManager = GameManager::GetInstance();
    _gameManager->SetScene(this);
    _gameManager->InitializeGame();

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    scheduleUpdate();
    return true;
}



void GameScene::update(float dt)
{
    //Run gameloop at update
    _gameManager->GameLoop(dt);

    //Check if player touched to screen, if touched, move player, getAnimatonInterval is for smoothness
    if (_isMoveable) {
        _playerMovementController->update(dt / Director::getInstance()->getAnimationInterval());
    }
   

}


//To detect collisions
bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    Node* shapeA = contact.getShapeA()->getBody()->getNode();
    Node* shapeB = contact.getShapeB()->getBody()->getNode();

    int tagA = shapeA->getTag();
    int tagB = shapeB->getTag();

    //Checking two contacted objects and their tags, if one of them's tag is player and other is enemyship, it is enemy playercollision
    if ((tagB == PLAYER_TAG && tagA == ENEMY_SHIP_TAG) || (tagA == PLAYER_TAG && tagB == ENEMY_SHIP_TAG)) {

        //Calling the function in collision manager to deal with this collision
        _collisionManager->EnemyPlayerCollision();
    }

    //Checking two contacted objects and their tags, if one of them's tag is ammo and other is enemyship, it is enemy bullet collision
    if ((tagB == AMMO_TAG && tagA == ENEMY_SHIP_TAG) || (tagA == AMMO_TAG && tagB == ENEMY_SHIP_TAG)) {
        
        Ammo* ammo;
        EnemyShip* enemyShip;
        if (tagA == AMMO_TAG) {
            ammo = (Ammo*)shapeA;
            enemyShip = (EnemyShip*)shapeB;
        }

        else {
            ammo = (Ammo*)shapeB;
            enemyShip = (EnemyShip*)shapeA;
        }

        //Calling the function in collision manager to deal with this collision
        _collisionManager->EnemyBulletCollision(enemyShip, ammo);
    }

    return true;
}

//When touch began
bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Player can move
    _isMoveable = true;

    //Getting touch position, if it is left of screen or right and declaring direction
    if (touch->getLocation().x < visibleSize.width / 2) {
        PlayerMovementController::GetInstance()->SetMovementDirection(-1);
    }

    else {
        PlayerMovementController::GetInstance()->SetMovementDirection(1);
    }
    
    return true;
}

//When touch ended, player cant move
bool GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    _isMoveable = false;
    return false;
}




