#ifndef __GAME_OVER_LAYER_H__
#define __GAME_OVER_LAYER_H__

#include "Support.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;

class GameOverLayer : public Layer {
public:
	CREATE_FUNC(GameOverLayer);
private:
	bool init();
};

#endif