#ifndef __ADD_JEWEL_NODE_H__
#define __ADD_JEWEL_NODE_H__

#include "Support.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace CocosDenshion;

class AddJewelNode : public Node {
public:
	static AddJewelNode* createNode(int count);
protected:
	bool initNode(int count);
};

#endif