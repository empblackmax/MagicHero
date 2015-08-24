#include "BossController.h"
#include "GameScene.h"
#include "AnimateManager.h"
#include "AddGoldNode.h"
#include "AddJewelNode.h"
#include "Boss.h"

BossController* BossController::createController(Boss *boss, int wallNode, Node *parent) {
	auto controller = new BossController();
	if (controller && controller->initController(boss, wallNode, parent)) {
		controller->autorelease();
		return controller;
	}
	CC_SAFE_DELETE(controller);
	return nullptr;
}

bool BossController::initController(Boss *boss, int wallNode, Node *parent) {
	_boss = boss;
	_wallNode = wallNode;
	_parent = parent;

	ValueMap bossMap = FileUtils::getInstance()->getValueMapFromFile(MONSTERTYPE_PLIST_NAME).at(_boss->getBossName()).asValueMap();
	auto armatureName = bossMap.at("armature_name").asString();
	ArmatureDataManager::getInstance()->addArmatureFileInfo(StringUtils::format("Boss/%s.ExportJson", armatureName.c_str()).c_str());
	_armature = Armature::create(armatureName);
	_boss->getShowSprite()->addChild(_armature);

	return true;
}


void BossController::run() {
	_armature->getAnimation()->play("run");
	this->schedule([=](float) {
		_boss->setPositionX(_boss->getPositionX() - _boss->getSpeed());
		if (_boss->getPositionX() < _wallNode + _armature->getContentSize().width * 0.5) {
			_boss->setPositionX(_wallNode + _armature->getContentSize().width * 0.5);
			_boss->setState(BossState::ATTACK);
		}
	}, "enemy_run");
}

void BossController::attack() {
	this->unschedule("enemy_run");
	_armature->getAnimation()->play("attack");
	this->schedule([=](float) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(WALLBEHIT_EFFECT_NAME);
		NotificationCenter::getInstance()->postNotification("enemy_attack", __Integer::create(_boss->getAttack()));
		if (_boss->getPositionX() > _wallNode) {
			_boss->setState(BossState::RUN);
		}
	}, 1, "enemy_attack");
}

void BossController::freeze() {
	this->unschedule("enemy_run");
	this->unschedule("enemy_attack");
	_armature->getAnimation()->play("freeze");
	this->scheduleOnce([=](float) {
		_boss->setState(BossState::RUN);
	}, 5, "enemy_freeze");
}

void BossController::death() {
	this->unschedule("enemy_run");
	this->unschedule("enemy_attack");
	if (DATAOPERATOR->getEffectEnable())
		AUDIOENGINE->playEffect(MONSTERDEAD_EFFECT_NAME);
	_armature->getAnimation()->play("death");
	NotificationCenter::getInstance()->postNotification("boss_death", __Integer::create(_boss->getGivenJewel()));
	DATAOPERATOR->setGold(DATAOPERATOR->getGold() + _boss->getGivenGold());
	auto gold = AddGoldNode::createNode(_boss->getGivenGold());
	gold->setPosition(_boss->getPosition());
	_parent->addChild(gold);

	auto cf = CallFunc::create([=]() {
		dynamic_cast<GameScene *>(_parent)->getEnemyArrayRM()->addObject(_boss);
		_boss->removeFromParent();
		if (CCRANDOM_0_1() > 0.9f) {
			DATAOPERATOR->setJewel(DATAOPERATOR->getJewel() + _boss->getGivenJewel());
			auto jewel = AddJewelNode::createNode(_boss->getGivenJewel());
			jewel->setPosition(_boss->getPosition());
			_parent->addChild(jewel);
		}
		NotificationCenter::getInstance()->postNotification("game_win");
	});
	auto seq = Sequence::create(DelayTime::create(3), cf, NULL);
	_boss->getShowSprite()->runAction(seq);
}