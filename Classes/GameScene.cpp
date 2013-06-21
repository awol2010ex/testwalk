#include "GameScene.h"
using namespace cocos2d;

GameScene::GameScene(void) {
	_gameLayer = NULL;
	_hudLayer = NULL;
}

GameScene::~GameScene(void) {
	delete _hudLayer;
	delete _gameLayer;
}

bool GameScene::init() {
	bool bRet = false;
	do {
		CC_BREAK_IF(!CCScene::init());

		CCSpriteFrameCache* cache =
					CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("sprite/charmeleon.plist", "sprite/charmeleon.png");
		cache->addSpriteFramesWithFile("UI.plist", "UI.png");

		_gameLayer = GameLayer::create();
		this->addChild(_gameLayer, 0);
		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer, 1);
		_hudLayer->getJoystick()->setDelegate(_gameLayer);//摇杆
		_gameLayer->setHud(_hudLayer);


		//定时同步按钮状态
		this->schedule(schedule_selector(GameScene::broadcastInput));
		bRet = true;
	} while (0);

	return bRet;
}


void GameScene::broadcastInput(float dt)
{
	_gameLayer->setInBtnState(_hudLayer->getInBtnState());
}
