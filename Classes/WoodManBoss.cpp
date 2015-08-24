#include "WoodManBoss.h"
#include "WoodManBossController.h"

WoodManBoss* WoodManBoss::createBoss(int wallNode, Node *parent) {
	auto boss = new WoodManBoss();
	if (boss && boss->initBoss(wallNode, parent)) {
		boss->autorelease();
		return boss;
	}
	CC_SAFE_DELETE(boss);
	return nullptr;
}

void WoodManBoss::hurt(int attack, float knockback) {
	if (!_shield) {
		_hp -= attack;
		if (_shield == false && CCRANDOM_0_1() > 0.9) {
			auto shield = Sprite::create("Boss/shield.png");
			shield->setScale(1.2f);
			this->addChild(shield, 1, "shield");
			_shield = true;
			this->scheduleOnce([=](float) {
				this->removeChildByName("shield");
				_shield = false;
			}, 1.5f, "shield_over");
		}
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
}

Rect WoodManBoss::getCollisionBox() {
	Rect nodeBox = _controller->getBossArmature()->getBoundingBox();
	Vec2 origin = this->convertToWorldSpace(nodeBox.origin);
	return Rect(origin.x + nodeBox.size.width * 0.5, origin.y, nodeBox.size.width * 0.5, nodeBox.size.height * 0.7);
}

bool WoodManBoss::initBoss(int wallNode, Node *parent) {
	_bossName = Value("WoodMan").asString();
	_wallNode = wallNode;
	_shield = false;
	this->setPosition(Vec2(SCREEN.width + 150, SCREEN.height * 0.5));
	_parent = parent;

	_showSprite = Sprite::create();
	this->addChild(_showSprite);

	ValueMap bossMap = FileUtils::getInstance()->getValueMapFromFile(MONSTERTYPE_PLIST_NAME).at(_bossName.c_str()).asValueMap();
	_givenGold = bossMap.at("given_gold").asInt();
	_givenJewel = bossMap.at("given_jewel").asInt();
	_knockbackResistance = bossMap.at("knockback_resistance").asFloat();
	_attack = bossMap.at("monster_attacka").asInt();
	_speed = bossMap.at("monster_speed").asInt();
	_hp = bossMap.at("monster_hp").asInt();
	_maxHp = _hp;

	_controller = WoodManBossController::createController(this, _wallNode, _parent);
	this->addChild(_controller);
	this->setState(BossState::RUN);

	Sprite *hpBG = Sprite::create("EnemyHPPanel.png");
	this->addChild(hpBG, 0, "hpBG");
	hpBG->setPositionY(-100);
	_hpPanel = Sprite::create("EnemyHP.png");
	this->addChild(_hpPanel, 1, "hpPanel");
	_hpPanel->setPositionY(-100);
	return true;
}
