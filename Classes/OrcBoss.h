#ifndef __ORC_BOSS_H__
#define __ORC_BOSS_H__

#include "Boss.h"

class OrcBoss : public Boss {
public:
	static OrcBoss* createBoss(int wallNode, Node *parent);
	Rect getCollisionBox();
private:
	bool initBoss(int wallNode, Node *parent);
};

#endif