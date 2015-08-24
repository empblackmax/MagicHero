#ifndef _BOSS_CONTROLLER_H__
#define _BOSS_CONTROLLER_H__

#include "Support.h"
#include "Controller.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocostudio;

class Boss;

class BossController : public Controller {
public:
	static BossController* createController(Boss *boss, int wallNode, Node *parent);
	virtual void run();
	virtual void attack();
	virtual void freeze();
	virtual void death();
protected:
	virtual bool initController(Boss *boss, int wallNode, Node *parent);
	Boss *_boss;
	int _wallNode;
	Node *_parent;
	CC_SYNTHESIZE_READONLY(Armature *, _armature, BossArmature);
};


#endif