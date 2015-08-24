#ifndef __LEVEL_BUTTON_H__
#define __LEVEL_BUTTON_H__

#include "Support.h"
USING_NS_CC;
using namespace CocosDenshion;

class LevelButton : public Node {
public:
	static LevelButton* createButton(int level, Vec2 pos, Node *parent);
protected:
	bool initButton(int level, Vec2 pos, Node *parent);
private:
	int _level;
	Node *_parent;

	bool _isLocked;
	Sprite *_showSprite;

	bool isTouchedInsert(Touch *pTouch);
	bool onTouchBegan(Touch *pTouch, Event *event);
	void onTouchMoved(Touch *pTouch, Event *event);
	void onTouchEnded(Touch *pTouch, Event *event);
};

#endif