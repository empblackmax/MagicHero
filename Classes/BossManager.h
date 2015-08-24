#ifndef __BOSS_MANAGER_H__
#define __BOSS_MANAGER_H__

#include "Support.h"
#include "Boss.h"
USING_NS_CC;

class BossManager {
public:
	static BossManager* getInstance();
	Boss* getBoss(int level, int wallNode, Node *parent);
};

#endif