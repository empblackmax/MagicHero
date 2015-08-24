#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Support.h"
#include "EnemyManager.h"
#include "Enemy.h"
USING_NS_CC;

class GameManager : public Node {
public:
	~GameManager();
	static GameManager* createManager(int level, int wallNode, Node *parent);
	void setCurrectHp(int hp);
	void setProgress(Node *progress);
protected:
	bool initManager(int level, int wallNode, Node *parent);
private:
	Node *_parent;
	EnemyManager *_enemyManager;
	CC_SYNTHESIZE(int, _currectLevel, CurrectLevel);
	CC_SYNTHESIZE(int, _currectMp, CurrectMp);
	CC_SYNTHESIZE_READONLY(int, _currectHp, CurrectHp);

	void beAttack(Ref *sender);
	void deployEnemy(float);
};

#endif