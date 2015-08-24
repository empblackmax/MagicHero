#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "Support.h"
#include "GameManager.h"
#include "Arrow.h"
#include "Bow.h"
#include "Enemy.h"
#include "Boss.h"
#include <vector>
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;

class GameScene : public Layer {
public:
	~GameScene();
	static Scene* createScene(int level);
	static GameScene* createGameScene(int level);
	Node* getBackground();
	void updateLabel();
protected:
	bool initScene(int level);
private:
	int _level;
	int _wallNode;
	Bow *_bow;
	Boss *_boss;
	Node *_panel;
	Node *_pause;
	Node * _background;

	GameManager *_manager;
	CC_SYNTHESIZE_READONLY(__Array *, _arrowArray, ArrowArray);
	CC_SYNTHESIZE_READONLY(__Array *, _enemyArray, EnemyArray);
	CC_SYNTHESIZE_READONLY(__Array *, _arrowArrayRM, ArrowArrayRM);
	CC_SYNTHESIZE_READONLY(__Array *, _enemyArrayRM, EnemyArrayRM);

	float _angle;
	bool _isShoot;
	int _airSpeed;
	void multpleArrows(int number);

	void initPanel();
	void initPause();
	void upgradeGroup(std::string groupName);

	void pauseGame();
	void resumeGame();

	void enemyDie(Ref *sender);
	void enemyOver(Ref *sender);
	void bossDie(Ref *sender);
	void gameWin(Ref *sender);
	void gameOver(Ref *sender);

	void card_Death(Ref *sender);
	void card_Judgement(Ref *sender);

	void loadResourse();
	void updateArray(float);
	void collisionListener(float);
	void setBowRotation(Touch *pTouch);

	ArrowState _arrowState;
	void freezeMagic();
	void lightingMagic();
	void freezeMagicAnimate(Vec2 v);
	void lightingMagicAnimate(Vec2 v);

	bool onTouchBegan(Touch *pTouch, Event *event);
	void onTouchMoved(Touch *pTouch, Event *event);
	void onTouchEnded(Touch *pTouch, Event *event);

	bool _isGetingJewel;
	ParticleSystemQuad *_fingerPoint;
	bool bossTouchBegan(Touch *pTouch, Event *event);
	void bossTouchMoved(Touch *pTouch, Event *event);
	void bossTouchEnded(Touch *pTouch, Event *event);
};

#endif