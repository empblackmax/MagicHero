#ifndef __BOW_H__
#define __BOW_H__

#include "Support.h"
#include "Entity.h"
USING_NS_CC;

class Bow : public Entity {
public:
	static Bow* createBow(Vec2 pos, Node *parent);
	int getProperty(std::string property);
	void setProperty(std::string property, int value);
protected:
	bool initBow(Vec2 pos, Node *parent);
private:
	Node *_parent;
	CC_SYNTHESIZE_READONLY(int, _power, Power);
	CC_SYNTHESIZE_READONLY(int, _speed, Speed);
	CC_SYNTHESIZE_READONLY(int, _range, Range);
	CC_SYNTHESIZE_READONLY(int, _multple, Multple);
	CC_SYNTHESIZE_READONLY(int, _airSpeed, AirSpeed);
	CC_SYNTHESIZE_READONLY(int, _knockBack, Knockback);
};

#endif