#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Pokemon.h"
class GameLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);

    //初始化地图
    void initTileMap();
    //精灵初始化
    void initPokemon() ;
    Pokemon *_pokemon;//精灵
    cocos2d::CCSpriteBatchNode *_actors;
    cocos2d::CCTMXTiledMap *_tileMap;//地图
};

#endif // __HELLOWORLD_SCENE_H__
