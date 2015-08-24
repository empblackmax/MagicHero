#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "Support.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;

class MenuScene : public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(MenuScene);
protected:
	bool init();
private:
	Node *_rootNode;
	void initButton();
};

#endif