#include "HudLayer.h"
using namespace cocos2d;
const float JOYSTICK_POS_X = 100;
const float JOYSTICK_POS_Y = 100;
const float JOYSTICK_DEAD_RADIUS = 10;
const float JOYSTICK_THRESHOLD = 0.4f;

const float BTN_A_POS_X = 430;
const float BTN_A_POS_Y = 50;
HudLayer::HudLayer(void) {
	//_dPad = NULL;
	//_actors = NULL;
}

HudLayer::~HudLayer(void) {
}

bool HudLayer::init() {
	bool bRet = false;
	do {
		CC_BREAK_IF(!CCLayer::init());
		//关闭按钮
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
				"CloseSelected.png", this,
				menu_selector(HudLayer::menuCloseCallback));
		pCloseItem->setPosition(
				ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

		// create menu, it's an autorelease object
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);
		/*
		 //batchNodes
		 _actors = CCSpriteBatchNode::create("pad/pad_and_button.png");
		 _actors->getTexture()->setAliasTexParameters();
		 this->addChild(_actors, -5);

		 CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(_actors->getTexture(),
		 CCRectMake(290, 215, 58, 58));

		 _dPad = SimpleDPad::dPadWithFrame(frame, 64);
		 _dPad->setPosition(ccp(64.0, 64.0));
		 _dPad->setOpacity(100);
		 _dPad->setScale(2.0);
		 _actors->addChild(_dPad);
		 */

		//初始化手柄
		mJoystick = NULL;
		mJoystick = new SneakyJoystickExt();
		mJoystick->initWithRect(CCRectZero);
		mJoystick->setAutoCenter(true);
		mJoystick->setHasDeadzone(true);
		mJoystick->setDeadRadius(JOYSTICK_DEAD_RADIUS);
		SneakyJoystickSkinnedBase* jstickSkin = new SneakyJoystickSkinnedBase();
		jstickSkin->autorelease();
		jstickSkin->init();
		jstickSkin->setBackgroundSprite(
				CCSprite::createWithSpriteFrameName("JoyStick-base.png"));
		jstickSkin->setThumbSprite(
				CCSprite::createWithSpriteFrameName("JoyStick-thumb.png"));
		jstickSkin->getThumbSprite()->setScale(2.0f);
		jstickSkin->getBackgroundSprite()->setScale(2.0f);
		jstickSkin->setPosition(ccp(JOYSTICK_POS_X, JOYSTICK_POS_Y));
		jstickSkin->setJoystick(mJoystick);
		this->addChild(jstickSkin);

		//按钮
		mButtonA = NULL;
		mButtonA = new SneakyButton();
		mButtonA->initWithRect(CCRectZero);
		mButtonA->setIsToggleable(false);
		mButtonA->setIsHoldable(true);
		SneakyButtonSkinnedBase* btnASkin = new SneakyButtonSkinnedBase();
		btnASkin->autorelease();
		btnASkin->init();
		btnASkin->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - BTN_A_POS_X, BTN_A_POS_Y));
		btnASkin->setDefaultSprite(
				CCSprite::createWithSpriteFrameName("button-default.png"));
		btnASkin->setPressSprite(
				CCSprite::createWithSpriteFrameName("button-pressed.png"));
		btnASkin->setActivatedSprite(
				CCSprite::createWithSpriteFrameName("button-activated.png"));
		//btnASkin->setDisabledSprite(CCSprite::createWithSpriteFrameName("button-disabled.png"));
		btnASkin->setButton(mButtonA);
		this->addChild(btnASkin);

		bRet = true;
	} while (0);

	return bRet;
}

void HudLayer::menuCloseCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


//按钮状态
InBtnState HudLayer::getInBtnState()
{
	InBtnState retState = IN_BTN_NO_PRESSED;

	if (mButtonA->getIsActive())
		retState = IN_BTN_PRESSED;

	return retState;
}
