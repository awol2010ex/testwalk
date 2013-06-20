#pragma once
#include "cocos2d.h"
//#include "SimpleDPad.h"

#include "Sneaky/SneakyButton.h"
#include "Sneaky/SneakyButtonSkinnedBase.h"
#include "Sneaky/SneakyJoystick.h"
#include "Sneaky/SneakyJoystickSkinnedBase.h"
#include "SneakyJoystickExt.h"
class HudLayer: public cocos2d::CCLayer {
public:
	HudLayer(void);
	~HudLayer(void);

	bool init();
	CREATE_FUNC (HudLayer);
	//CC_SYNTHESIZE(SimpleDPad*, _dPad, DPad);//方向键

	// a selector callback
	void menuCloseCallback(CCObject* pSender);
	CC_SYNTHESIZE(SneakyJoystickExt*, mJoystick, Joystick); //手柄

	//cocos2d::CCSpriteBatchNode *_actors;

};
