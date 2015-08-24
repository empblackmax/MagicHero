#ifndef __BOW_BUTTON_H__
#define __BOW_BUTTON_H__

#include "Support.h"
USING_NS_CC;
using namespace CocosDenshion;

enum class BowButtonState {
	LOCKED,
	UNLOCK_UNSELECTED,
	UNLOCK_SELECTED
};

class BowButton : public Node {
public:
	static BowButton* createButton(std::string bowName, Vec2 pos, __Array *preSkill, Node *parent);
	~BowButton();
	void unlock();
	void select();
	void unselect();
protected:
	bool initButton(std::string bowName, Vec2 pos, __Array *preSkill, Node *parent);
private:
	std::string _bowName;
	BowButtonState _state;
	__Array *_preSkill;
	Node *_parent;

	Sprite *_showSprite;
	Sprite *_selectShade;
	SpriteFrame *_up;
	SpriteFrame *_down;
	SpriteFrame *_lock;

	bool isUpgradeEnable();
	bool isTouchedInsert(Touch *pTouch);

	bool onTouchBegan(Touch *pTouch, Event *event);
	void onTouchMoved(Touch *pTouch, Event *event);
	void onTouchEnded(Touch *pTouch, Event *event);
};

#endif