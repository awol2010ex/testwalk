#include "Pokemon.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

Pokemon::Pokemon(void) {
}

Pokemon::~Pokemon(void) {
}

bool Pokemon::init(CCSpriteBatchNode* _actors) {

	bool bRet = false;
	do {
		int i;
		CCSpriteFrame *frame = NULL;
		//idle animation
		CCArray *idleFrames = CCArray::createWithCapacity(2);

		frame = CCSpriteFrame::createWithTexture(_actors->getTexture(),
				CCRectMake(20, 40, 60, 60));
		idleFrames->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(_actors->getTexture(),
				CCRectMake(80, 40, 60, 60));
		idleFrames->addObject(frame);

		//初始
		CC_BREAK_IF(
				!ActionSprite::initWithSpriteFrame(
						(CCSpriteFrame*) idleFrames->objectAtIndex(0)));

		CCAnimation *idleAnimation = CCAnimation::createWithSpriteFrames(
				idleFrames, 0.2);
		this->setIdleAction(
				CCRepeatForever::create(CCAnimate::create(idleAnimation)));

		//walk animation
		CCArray *walkFrames = CCArray::createWithCapacity(3);
		frame = CCSpriteFrame::createWithTexture(_actors->getTexture(),
				CCRectMake(170, 40, 70, 70));
		walkFrames->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(_actors->getTexture(),
				CCRectMake(240, 40, 70, 70));
		walkFrames->addObject(frame);
		frame = CCSpriteFrame::createWithTexture(_actors->getTexture(),
				CCRectMake(310, 40, 70, 70));
		walkFrames->addObject(frame);
		CCAnimation *walkAnimation = CCAnimation::createWithSpriteFrames(walkFrames, float(1.0 / 12.0));
		this->setWalkAction(CCRepeatForever::create(CCAnimate::create(walkAnimation)));

		//中心距离
		this->setCenterToBottom(35.0);
		this->setCenterToSides(35.0);

		//步速
		this->setWalkSpeed(80.0);

		//初始方向
		this->setDirect(-1.0);
		bRet = true;
	} while (0);

	return bRet;
}

void Pokemon::knockout() {
	ActionSprite::knockout();
}

Pokemon* Pokemon::createWithBatchNode(CCSpriteBatchNode* _actors) {
	Pokemon *pRet = new Pokemon();
	if (pRet && pRet->init(_actors)) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
