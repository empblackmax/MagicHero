#include "Boss.h"

Boss* Boss::createBoss(std::string bossName, int wallNode, Vec2 pos, Node *parent) {
	Boss *boss = new Boss();
	if (boss && boss->initBoss(bossName, wallNode, pos, parent)) {
		boss->autorelease();
		return boss;
	}
	CC_SAFE_DELETE(boss);
	return nullptr;
}

Sprite* Boss::getShowSprite() {
	return _showSprite;
}

void Boss::hurt(int attack, float knockback) {
	_hp -= attack;
	float knock = knockback * _knockbackResistance;
	this->setPositionX(this->getPositionX() + knock);
	_hpPanel->setScaleX((float)_hp / _maxHp);
	if (_state != BossState::DEATH && _hp <= 0) {
		_hp = 0;
		_hpPanel->setVisible(false);
		this->setState(BossState::DEATH);
		_showSprite->removeChildByName("hpBG");
	}
}

void Boss::setState(BossState state) {
	_state = state;
	switch (state) {
	case BossState::RUN:
		_controller->run();
		break;
	case BossState::ATTACK:
		_controller->attack();
		break;
	case BossState::FREEZR:
		_controller->freeze();
		break;
	case BossState::DEATH:
		_controller->death();
		break;
	case BossState::BossStateCount:
		break;
	default:
		break;
	}
}

Rect Boss::getCollisionBox() {
	Rect nodeBox = _armature->getBoundingBox();
	Vec2 origin = this->convertToWorldSpace(nodeBox.origin);
	return Rect(origin.x + nodeBox.size.width * 0.5, origin.y, nodeBox.size.width * 0.5, nodeBox.size.height * 0.7);
}

bool Boss::initBoss(std::string bossName, int wallNode, Vec2 pos, Node *parent) {
	_bossName = Value(bossName).asString();
	_wallNode = wallNode;
	this->setPosition(pos);
	_parent = parent;

	_showSprite = Sprite::create();
	this->addChild(_showSprite);

	ValueMap bossMap = FileUtils::getInstance()->getValueMapFromFile(MONSTERTYPE_PLIST_NAME).at(bossName.c_str()).asValueMap();
	_givenGold = bossMap.at("given_gold").asInt();
	_givenJewel = bossMap.at("given_jewel").asInt();
	_knockbackResistance = bossMap.at("knockback_resistance").asFloat();
	_attack = bossMap.at("monster_attacka").asInt();
	_speed = bossMap.at("monster_speed").asInt();
	_hp = bossMap.at("monster_hp").asInt();
	_maxHp = _hp;

	_controller = BossController::createController(this, _wallNode, _parent);
	this->addChild(_controller);
	this->setState(BossState::RUN);

	Sprite *hpBG = Sprite::create("bossHPPanel.png");
	this->addChild(hpBG, 0, "hpBG");
	hpBG->setPositionY(-70);
	hpBG->setScale(0.3f);
	_hpPanel = Sprite::create("bossHP.png");
	this->addChild(_hpPanel, 1, "hpPanel");
	_hpPanel->setPositionY(-70);
	_hpPanel->setScale(0.3f);

	return true;
}