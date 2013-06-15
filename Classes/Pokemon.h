#pragma once
#include "actionsprite.h"
using namespace cocos2d;
class Pokemon : public ActionSprite
{
public:
	Pokemon(void);
	~Pokemon(void);


	bool init(CCSpriteBatchNode* _actors);
	void knockout();

	static Pokemon* createWithBatchNode(CCSpriteBatchNode* _actors);
};
