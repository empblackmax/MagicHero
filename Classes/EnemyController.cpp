#include "EnemyController.h"
#include "GameScene.h"
#include "AnimateManager.h"
#include "AddGoldNode.h"
#include "AddJewelNode.h"
#include "Card.h"

EnemyController::~EnemyController() {
	CC_SAFE_RELEASE(_run);
	CC_SAFE_RELEASE(_attack);
	CC_SAFE_RELEASE(_freeze);
	CC_SAFE_RELEASE(_death);
}

EnemyController* EnemyController::createController(Enemy *enemy, int wallNode, Node *parent) {
	EnemyController *controller = new EnemyController();
	if (controller && controller->initController(enemy, wallNode, parent)) {
		controller->autorelease();
		return controller;
	}
	CC_SAFE_DELETE(controller);
	return nullptr;
}

bool EnemyController::initController(Enemy *enemy, int wallNode, Node *parent) {
	_enemy = enemy;
	_parent = parent;
	_wallNode = wallNode;

	_run = initAnimate(RUN_ANIMATE_KEY, -1);
	_attack = initAnimate(ATTACK_ANIMATE_KEY, -1);
	_freeze = initAnimate(FREEZE_ANIMATE_KEY);
	_death = initAnimate(DEATH_ANIMATE_KEY, 1);

	CC_SAFE_RETAIN(_run);
	CC_SAFE_RETAIN(_attack);
	CC_SAFE_RETAIN(_freeze);
	CC_SAFE_RETAIN(_death);

	return true;
}

void EnemyController::run() {
	_enemy->getShowSprite()->stopAllActions();
	_enemy->getShowSprite()->runAction(_run);
	this->schedule([=](float) {
		_enemy->setPositionX(_enemy->getPositionX() - _enemy->getSpeed());
		if (_enemy->getPositionX() < _wallNode + _enemy->getShowSprite()->getBoundingBox().size.width * 0.5) {
			_enemy->setPositionX(_wallNode + _enemy->getShowSprite()->getBoundingBox().size.width * 0.5);
			_enemy->setState(EnemyState::ATTACK);
		}
	}, "enemy_run");
}

void EnemyController::attack() {
	this->unschedule("enemy_run");
	_enemy->getShowSprite()->stopAllActions();
	_enemy->getShowSprite()->runAction(_attack);
	this->schedule([=](float) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(WALLBEHIT_EFFECT_NAME);
		NotificationCenter::getInstance()->postNotification("enemy_attack", __Integer::create(_enemy->getAttack()));
		if (_enemy->getPositionX() > _wallNode) {
			_enemy->setState(EnemyState::RUN);
		}
	}, 1, "enemy_attack");
}

void EnemyController::freeze() {
	this->unschedule("enemy_run");
	this->unschedule("enemy_attack");
	_enemy->getShowSprite()->stopAllActions();
	_enemy->getShowSprite()->runAction(_freeze);
	this->scheduleOnce([=](float) {
		_enemy->setState(EnemyState::RUN);
	}, 5, "enemy_freeze");
}

void EnemyController::death() {
	if (DATAOPERATOR->getEffectEnable())
		AUDIOENGINE->playEffect(MONSTERDEAD_EFFECT_NAME);
	this->unschedule("enemy_run");
	this->unschedule("enemy_attack");
	_enemy->getShowSprite()->stopAllActions();

	DATAOPERATOR->setGold(DATAOPERATOR->getGold() + _enemy->getGivenGold());
	auto gold = AddGoldNode::createNode(_enemy->getGivenGold());
	gold->setPosition(_enemy->getPosition());
	_parent->addChild(gold);

	auto out = FadeOut::create(1);
	auto cf = CallFunc::create([=]() {
		dynamic_cast<GameScene *>(_parent)->getEnemyArrayRM()->addObject(_enemy);
		_enemy->removeFromParent();
		NotificationCenter::getInstance()->postNotification("enemy_die", __Integer::create(_enemy->getGivenJewel()));
		if (CCRANDOM_0_1() > 0.9f) {
			DATAOPERATOR->setJewel(DATAOPERATOR->getJewel() + _enemy->getGivenJewel());
			auto jewel = AddJewelNode::createNode(_enemy->getGivenJewel());
			jewel->setPosition(_enemy->getPosition());
			_parent->addChild(jewel);
		}
		if (CCRANDOM_0_1() > 0.7f) {
			_parent->addChild(Card::createCard(_enemy->getPosition(), _parent));
		}
	});
	auto seq = Sequence::create(_death, out, cf, NULL);
	_enemy->getShowSprite()->runAction(seq);
}

Animate* EnemyController::initAnimate(const char *type, int loop, float delay) {
	auto manager = AnimateManager::getInstance();
	ValueMap enemyMap = FileUtils::getInstance()->getValueMapFromFile(MONSTERTYPE_PLIST_NAME).at(_enemy->getEnemyName()).asValueMap();
	auto animateMap = enemyMap.at(type).asValueMap();
	auto frameName = animateMap.at(ANIMATE_FRAME_NAME_KEY).asString();
	auto frameCount = animateMap.at(ANIMATE_FRAME_COUNT_KEY).asInt();
	return manager->getAnimate(frameName.c_str(), frameCount, loop, delay);
}