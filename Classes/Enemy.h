#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Support.h"
#include "Entity.h"
#include "EnemyController.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocostudio;

enum class EnemyState {
	RUN,
	ATTACK,
	FREEZR,
	DEATH,
	EnemyStateCount
};

class Enemy : public Entity {
public:
	static Enemy* createEnemy(std::string enemyName, int wallNode, Vec2 pos, Node *parent);
	Sprite* getShowSprite();
	virtual void hurt(int attack, float knockback);
	void setState(EnemyState state);
	virtual Rect getCollisionBox();
protected:
	virtual bool initEnemy(std::string enemyName, int wallNode, Vec2 pos, Node *parent);

	int _maxHp;
	int _wallNode;
	Node *_parent;
	EnemyController *_controller;
	Sprite *_hpPanel;
	CC_SYNTHESIZE(int, _hp, Hp);
	CC_SYNTHESIZE_READONLY(std::string, _enemyName, EnemyName);
	CC_SYNTHESIZE_READONLY(EnemyState, _state, State);
	CC_SYNTHESIZE_READONLY(Armature *, _armature, EnemyArmature);
	CC_SYNTHESIZE_READONLY(int, _givenGold, GivenGold);
	CC_SYNTHESIZE_READONLY(int, _givenJewel, GivenJewel);
	CC_SYNTHESIZE_READONLY(float, _knockbackResistance, KnockbackResistance);
	CC_SYNTHESIZE_READONLY(int, _attack, Attack);
	CC_SYNTHESIZE_READONLY(int, _speed, Speed);
};

#endif