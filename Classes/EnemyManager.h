#ifndef __ENEMY_MANAGER_H__
#define __ENEMY_MANAGER_H__

#include "Support.h"
#include "Enemy.h"
USING_NS_CC;

class EnemyManager : public Node {
public:
	~EnemyManager();
	static EnemyManager* createManager(int level, int wallNode, Node *parent);
	Enemy* createEnemy(Vec2 pos);
protected:
	bool initManager(int level, int wallNode, Node *parent);
private:
	int _level;
	int _wallNode;
	Node *_parent;
	ValueVector _nomalEnemyList;
	ValueVector _eliteEnemyList;

	CC_SYNTHESIZE_READONLY(int, _leftEnemy, LeftEnemy);
	CC_SYNTHESIZE_READONLY(int, _surplusEnemy, SurplusEnemy);
	CC_SYNTHESIZE_READONLY(int, _totalEnemy, TotalEnemy);
	CC_SYNTHESIZE_READONLY(int, _eliteEnemy, EliteEnemy);

	void loadResourse();
	void enemyDie(Ref *sender);
};

#endif