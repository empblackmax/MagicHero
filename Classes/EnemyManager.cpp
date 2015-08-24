#include "EnemyManager.h"

EnemyManager::~EnemyManager() {
	NotificationCenter::getInstance()->removeAllObservers(this);
}

EnemyManager* EnemyManager::createManager(int level, int wallNode, Node *parent) {
	EnemyManager *manager = new EnemyManager();
	if (manager && manager->initManager(level, wallNode, parent)) {
		manager->autorelease();
		return manager;
	}
	CC_SAFE_DELETE(manager);
	return nullptr;
}

Enemy* EnemyManager::createEnemy(Vec2 pos) {
	int num = 0;
	Enemy *enemy = nullptr;
	if (_surplusEnemy > _eliteEnemy) {
		num = static_cast<int>(CCRANDOM_0_1() * _nomalEnemyList.size());
		enemy = Enemy::createEnemy(_nomalEnemyList.at(num).asString(), _wallNode, pos, _parent);
		_surplusEnemy--;
	}
	else if (_surplusEnemy > 0) {
		int num = static_cast<int>(CCRANDOM_0_1() * _eliteEnemyList.size());
		enemy = Enemy::createEnemy(_eliteEnemyList.at(num).asString(), _wallNode, pos, _parent);
		_surplusEnemy--;
	}
	
	return enemy;
}

bool EnemyManager::initManager(int level, int wallNode, Node *parent) {
	this->loadResourse();
	_level = level;
	_parent = parent;
	_wallNode = wallNode;

	ValueMap fileMap = FileUtils::getInstance()->getValueMapFromFile(StringUtils::format("LevelSetting/Level_%02d.plist", _level).c_str());
	_surplusEnemy = fileMap.at("enemy_count").asInt();
	_totalEnemy = fileMap.at("enemy_count").asInt();
	_eliteEnemy = fileMap.at("senior_limit").asInt();
	_nomalEnemyList = fileMap.at("monster_name").asValueVector();
	_eliteEnemyList = fileMap.at("senior_monster_name").asValueVector();
	_leftEnemy = _totalEnemy;

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(EnemyManager::enemyDie), "enemy_die", NULL);
	return true;
}

void EnemyManager::loadResourse() {

}

void EnemyManager::enemyDie(Ref *sender) {
	_leftEnemy -= 1;
	if (_leftEnemy <= 0)
		NotificationCenter::getInstance()->postNotification("enemy_over");
}