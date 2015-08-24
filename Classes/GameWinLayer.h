#ifndef __GAME_WIN_LAYER_H__
#define __GAME_WIN_LAYER_H__

#include "Support.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;

class GameWinLayer : public Layer {
public:
	static GameWinLayer* createLayer(int level);
private:
	bool initLayer(int level);
};

#endif