#ifndef __WOOD_MAN_BOSS_H__
#define __WOOD_MAN_BOSS_H__

#include "Boss.h"

class WoodManBoss : public Boss {
public:
	static WoodManBoss* createBoss(int wallNode, Node *parent);
	virtual void hurt(int attack, float knockback);
	Rect getCollisionBox();
private:
	bool initBoss(int wallNode, Node *parent);
	bool _shield;
};

#endif