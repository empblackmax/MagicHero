#ifndef __BOSS_H__
#define __BOSS_H__

#include "Support.h"
#include "Entity.h"
#include "BossController.h"
USING_NS_CC;
using namespace cocostudio;
using namespace CocosDenshion;

enum class BossState {
	RUN,
	ATTACK,
	FREEZR,
	DEATH,
	BossStateCount
};

class Boss : public Entity {
public:
	static Boss* createBoss(std::string bossName, int wallNode, Vec2 pos, Node *parent);
	Sprite* getShowSprite();
	virtual void hurt(int attack, float knockback);
	void setState(BossState state);
	virtual Rect getCollisionBox();
protected:
	virtual bool initBoss(std::string bossName, int wallNode, Vec2 pos, Node *parent);

	int _maxHp;
	int _wallNode;
	Node *_parent;
	BossController *_controller;
	Sprite *_hpPanel;
	CC_SYNTHESIZE(int, _hp, Hp);
	CC_SYNTHESIZE_READONLY(std::string, _bossName, BossName);
	CC_SYNTHESIZE_READONLY(BossState, _state, State);
	CC_SYNTHESIZE_READONLY(Armature *, _armature, BossArmature);
	CC_SYNTHESIZE_READONLY(int, _givenGold, GivenGold);
	CC_SYNTHESIZE_READONLY(int, _givenJewel, GivenJewel);
	CC_SYNTHESIZE_READONLY(float, _knockbackResistance, KnockbackResistance);
	CC_SYNTHESIZE_READONLY(int, _attack, Attack);
	CC_SYNTHESIZE_READONLY(int, _speed, Speed);
};

#endif