#include "Pokemon.h"
#include "GameLayer.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameLayer::GameLayer(void) {
	_pokemon = NULL;
	_actors = NULL;
	_tileMap = NULL;
}

GameLayer::~GameLayer(void) {
	this->unscheduleUpdate();
}

// on "init" you need to initialize your instance
bool GameLayer::init() {
	bool bRet = false;
	do {
		CC_BREAK_IF(!CCLayer::init());

		this->setTouchEnabled(true);


		//初始化地图
		this->initTileMap();

		//batchNodes
		_actors = CCSpriteBatchNode::create("sprite/charmeleon.png");
		_actors->getTexture()->setAliasTexParameters();
		this->addChild(_actors, -5);

		//初始化精灵
		this->initPokemon();

		this->scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;

	return true;
}



//初始化地图
void GameLayer::initTileMap() {
	_tileMap = CCTMXTiledMap::create("map/0000000_hotel.tmx");
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(_tileMap->getChildren(), pObject)
	{
		CCTMXLayer *child = (CCTMXLayer*) pObject;
		child->getTexture()->setAliasTexParameters();
	}
	this->addChild(_tileMap, -6);
}
//精灵初始化
void GameLayer::initPokemon() {

	_pokemon = Pokemon::createWithBatchNode(_actors);

	_actors->addChild(_pokemon);
	_pokemon->setPosition(ccp(_pokemon->getCenterToSides() + 200, 80));
	_pokemon->setDesiredPosition(_pokemon->getPosition());
	_pokemon->idle();

}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {

}

void GameLayer::didChangeDirectionTo(SimpleDPad *simpleDPad,
		CCPoint direction) {
	_pokemon->walkWithDirection(direction);
}

void GameLayer::isHoldingDirection(SimpleDPad *simpleDPad, CCPoint direction) {
	_pokemon->walkWithDirection(direction);
}

void GameLayer::simpleDPadTouchEnded(SimpleDPad *simpleDPad) {
	if (_pokemon->getActionState() == kActionStateWalk) {
		_pokemon->idle();
	}
}

//实时更新
void GameLayer::update(float dt) {
	_pokemon->update(dt);
	this->updatePositions();
	this->reorderActors();
	this->setViewpointCenter(_pokemon->getPosition());
}
//更新位置
void GameLayer::updatePositions() {
	float posX = MIN(
			_tileMap->getMapSize().width * _tileMap->getTileSize().width
					- _pokemon->getCenterToSides(),
			MAX(_pokemon->getCenterToSides(), _pokemon->getDesiredPosition().x));
	float posY = MIN(
			_tileMap->getMapSize().height *_tileMap->getTileSize().height - _pokemon->getCenterToBottom(),
			MAX(_pokemon->getCenterToBottom(),
					_pokemon->getDesiredPosition().y));
	_pokemon->setPosition(ccp(posX, posY));

}
//更新地图位置
void GameLayer::setViewpointCenter(CCPoint position) {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x,
			(_tileMap->getMapSize().width * _tileMap->getTileSize().width)
					- winSize.width / 2);
	y = MIN(y,
			(_tileMap->getMapSize().height * _tileMap->getTileSize().height)
					- winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}
//重新对batchNode排序
void GameLayer::reorderActors() {
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(_actors->getChildren(), pObject)
	{
		ActionSprite *sprite = (ActionSprite*) pObject;
		_actors->reorderChild(sprite,
				(_tileMap->getMapSize().height * _tileMap->getTileSize().height)
						- sprite->getPosition().y);
	}
}
