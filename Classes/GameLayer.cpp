#include "Pokemon.h"
#include "GameLayer.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }


    this->setTouchEnabled(true);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameLayer::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);


    //初始化地图
    this->initTileMap();

    //batchNodes
    _actors = CCSpriteBatchNode::create("sprite/charmeleon.png");
    _actors->getTexture()->setAliasTexParameters();
    this->addChild(_actors, -5);

    //初始化精灵
    this->initPokemon() ;

    return true;
}

void GameLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
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
	_pokemon->setPosition(ccp(_pokemon->getCenterToSides()+200, 80));
	_pokemon->setDesiredPosition(_pokemon->getPosition());
	_pokemon->idle();


}
