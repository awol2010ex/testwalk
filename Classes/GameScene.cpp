#include "GameScene.h"
using namespace cocos2d;

GameScene::GameScene(void)
{
	_gameLayer = NULL;
}

GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		 
		_gameLayer = GameLayer::create();
		this->addChild(_gameLayer, 0);

		bRet = true;
	} while (0);

	return bRet;
}
