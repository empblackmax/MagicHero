#ifndef __ADD_GOLD_NODE_H__
#define __ADD_GOLD_NODE_H__

#include "Support.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace CocosDenshion;

class AddGoldNode : public Node {
public:
	static AddGoldNode* createNode(int count);
protected:
	bool initNode(int count);
};

#endif