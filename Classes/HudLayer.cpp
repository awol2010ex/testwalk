#include "HudLayer.h"
using namespace cocos2d;

HudLayer::HudLayer(void) {
	_dPad = NULL;
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

		CCSpriteFrame *frame = CCSpriteFrame::create("pad/pad_and_button.png",
				CCRectMake(290, 215, 58, 58));

		_dPad = SimpleDPad::dPadWithFrame(frame, 64);
		_dPad->setPosition(ccp(64.0, 64.0));
		_dPad->setOpacity(100);
		_dPad->setScale(2.0);
		this->addChild(_dPad);

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
