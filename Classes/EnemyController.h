#ifndef __ENEMY_CONTROLLER_H__
#define __ENEMY_CONTROLLER_H__

#include "Support.h"
#include "Controller.h"
USING_NS_CC;
using namespace cocostudio;

class Enemy;

class EnemyController : public Controller {
public:
	~EnemyController();
	static EnemyController* createController(Enemy *enemy, int wallNode, Node *parent);
	virtual void run();
	virtual void attack();
	virtual void freeze();
	virtual void death();
protected:
	virtual bool initController(Enemy *enemy, int wallNode, Node *parent);

	Enemy *_enemy;
	Node *_parent;
	int _wallNode;
	Animate *_run;
	Animate *_attack;
	Animate *_freeze;
	Animate *_death;

	Animate* initAnimate(const char *type, int loop = 0, float delay = 0.08);
};

#endif