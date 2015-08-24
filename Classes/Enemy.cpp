#include "Enemy.h"

Enemy* Enemy::createEnemy(std::string enemyName, int wallNode, Vec2 pos, Node *parent) {
	Enemy *enemy = new Enemy();
	if (enemy && enemy->initEnemy(enemyName, wallNode, pos, parent)) {
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

Sprite* Enemy::getShowSprite() {
	return _showSprite;
}

void Enemy::hurt(int attack, float knockback) {
	_hp -= attack;
	float knock = knockback * _knockbackResistance;
	this->setPositionX(this->getPositionX() + knock);
	_hpPanel->setScaleX((float)_hp / _maxHp * 0.3);
	if (_state != EnemyState::DEATH && _hp <= 0) {
		_hp = 0;
		_hpPanel->setVisible(false);
		this->setState(EnemyState::DEATH);
		_showSprite->removeChildByName("hpBG");
	}
}

void Enemy::setState(EnemyState state) {
	_state = state;
	switch (state) {
	case EnemyState::RUN:
		_controller->run();
		break;
	case EnemyState::ATTACK:
		_controller->attack();
		break;
	case EnemyState::FREEZR:
		_controller->freeze();
		break;
	case EnemyState::DEATH:
		_controller->death();
		break;
	case EnemyState::EnemyStateCount:
		break;
	default:
		break;
	}
}

Rect Enemy::getCollisionBox() {
	Rect nodeBox = _showSprite->getBoundingBox();
	Vec2 origin = this->convertToWorldSpace(nodeBox.origin);
	return Rect(origin.x + nodeBox.size.width * 0.5, origin.y, nodeBox.size.width * 0.5, nodeBox.size.height * 0.7);
}

bool Enemy::initEnemy(std::string enemyName, int wallNode, Vec2 pos, Node *parent) {
	_enemyName = Value(enemyName).asString();
	_wallNode = wallNode;
	this->setPosition(pos);
	_parent = parent;

	_showSprite = Sprite::create();
	this->addChild(_showSprite);

	ValueMap enemyMap = FileUtils::getInstance()->getValueMapFromFile(MONSTERTYPE_PLIST_NAME).at(enemyName.c_str()).asValueMap();
	_givenGold = enemyMap.at("given_gold").asInt();
	_givenJewel = enemyMap.at("given_jewel").asInt();
	_knockbackResistance = enemyMap.at("knockback_resistance").asFloat();
	_attack = enemyMap.at("monster_attacka").asInt();
	_speed = enemyMap.at("monster_speed").asInt();
	_hp = enemyMap.at("monster_hp").asInt();
	_maxHp = _hp;

	_controller = EnemyController::createController(this, _wallNode, _parent);
	this->addChild(_controller);
	this->setState(EnemyState::RUN);

	Sprite *hpBG = Sprite::create("EnemyHPPanel.png");
	this->addChild(hpBG, 0, "hpBG");
	hpBG->setPositionY(-70);
	hpBG->setScale(0.3f);
	_hpPanel = Sprite::create("EnemyHP.png");
	this->addChild(_hpPanel, 1, "hpPanel");
	_hpPanel->setPositionY(-70);
	_hpPanel->setScale(0.3f);

	return true;
}