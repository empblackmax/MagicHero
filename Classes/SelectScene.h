#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__

#include "Support.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;

class SelectScene : public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(SelectScene);
	void unselectBowButton();
	void updateLabel();
protected:
	bool init();
private:
	Text *_jewel;
	Text *_gold;

	Node *_bowLayer;
	Node *_levelLayer;
	void initBowLayer();
	void initLevelLayer();
};

#endif