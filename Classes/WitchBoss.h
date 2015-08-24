#ifndef __WITCH_BOSS_H__
#define __WITCH_BOSS_H__

#include "Boss.h"

class WitchBoss : public Boss {
public:
	static WitchBoss* createBoss(int wallNode, Node *parent);
	virtual void hurt(int attack, float knockback);
	Rect getCollisionBox();
private:
	bool initBoss(int wallNode, Node *parent);
};

#endif