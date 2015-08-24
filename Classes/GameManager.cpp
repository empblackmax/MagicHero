#include "GameManager.h"
#include "GameScene.h"
#include "OrcBoss.h"

GameManager::~GameManager() {
	NotificationCenter::getInstance()->removeAllObservers(this);
}

GameManager* GameManager::createManager(int level, int wallNode, Node *parent) {
	GameManager *manager = new GameManager();
	if (manager && manager->initManager(level, wallNode, parent)) {
		manager->autorelease();
		return manager;
	}
	CC_SAFE_DELETE(manager);
	return nullptr;
}

void GameManager::setCurrectHp(int hp) {
	_currectHp = hp;
	dynamic_cast<GameScene *>(_parent)->updateLabel();
	if (_currectHp <= 0) {
		_currectHp = 0;
		NotificationCenter::getInstance()->postNotification("game_over");
	}
}

void GameManager::setProgress(Node *progress) {
	progress->setPositionX(450 + 220 * ((float)_enemyManager->getLeftEnemy() / _enemyManager->getTotalEnemy()));
}

bool GameManager::initManager(int level, int wallNode, Node *parent) {
	_currectLevel = level;
	_parent = parent;

	_currectHp = DATAOPERATOR->getMaxHp();
	_currectMp = DATAOPERATOR->getMaxMp();

	_enemyManager = EnemyManager::createManager(_currectLevel, wallNode, _parent);
	this->addChild(_enemyManager);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameManager::beAttack), "enemy_attack", NULL);
	this->schedule(schedule_selector(GameManager::deployEnemy), 3);

	return true;
}

void GameManager::beAttack(Ref *sender) {
	int attack = dynamic_cast<__Integer *>(sender)->getValue();
	this->setCurrectHp(this->getCurrectHp() - attack);
}

void GameManager::deployEnemy(float) {
	Vec2 pos = Vec2(SCREEN.width + 50, 100 + CCRANDOM_0_1() * 280);
	auto enemy = _enemyManager->createEnemy(pos);
	if (enemy) {
		enemy->setLocalZOrder(500 - enemy->getPositionY());
		auto scene = dynamic_cast<GameScene *>(_parent);
		scene->getBackground()->addChild(enemy);
		scene->getEnemyArray()->addObject(enemy);
	}
}