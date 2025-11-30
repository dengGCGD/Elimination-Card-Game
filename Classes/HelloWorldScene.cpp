#include "HelloWorldScene.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto* 

    _gameController = new GameController();
    _gameController->init();
    _gameController->startGame();
    this->addChild(_gameController->getGameView());

    return true;
}