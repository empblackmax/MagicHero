#ifndef __CARD_H__
#define __CARD_H__

#include "Support.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;

class Card : public Node {
public:
	static Card* createCard(Vec2 pos, Node *parent);
private:
	bool initCard(Vec2 pos, Node *parent);
};

#endif