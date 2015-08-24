#ifndef __ARROW_H__
#define __ARROW_H__

#include "Support.h"
#include "Entity.h"
USING_NS_CC;

enum class ArrowState {
	NORMAL,
	FIRE,
	ArrowStateCount
};

class Arrow : public Entity{
public:
	static Arrow* createArrow(Vec2 pos, float angle, int flyspeed, ArrowState state, Node *parent);
	Vec2 getCollisionPoint();
protected:
	bool initArrow(Vec2 pos, float angle, int flyspeed, ArrowState state, Node *parent);
private:
	Node *_parent;
	ArrowState _state;
	CC_SYNTHESIZE_READONLY(int, _flyspeed, Flyspeed);

	Vec2 getNormalizedByAngle(float angle);
};

#endif