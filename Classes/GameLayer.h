#pragma once
#include "cocos2d.h"
#include "Pokemon.h"
#include "SimpleDPad.h"

#include "HudLayer.h"
class GameLayer: public cocos2d::CCLayer, public SimpleDPadDelegate {
public:
	GameLayer(void);
	~GameLayer(void);

	CREATE_FUNC (GameLayer);
	bool init();
	//初始化地图
	void initTileMap();
	//精灵初始化
	void initPokemon();

	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches,
			cocos2d::CCEvent *pEvent);

	virtual void didChangeDirectionTo(SimpleDPad *simpleDPad,
			cocos2d::CCPoint direction);
	virtual void isHoldingDirection(SimpleDPad *simpleDPad,
			cocos2d::CCPoint direction);
	virtual void simpleDPadTouchEnded(SimpleDPad *simpleDPad);

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	Pokemon *_pokemon; //精灵
	cocos2d::CCSpriteBatchNode *_actors;
	cocos2d::CCTMXTiledMap *_tileMap; //地图

	//操作层
	CC_SYNTHESIZE(HudLayer*, _hud, Hud);
};
