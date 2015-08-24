#include "GameScene.h"
#include "SelectScene.h"
#include "GameWinLayer.h"
#include "GameOverLayer.h"
#include "CsvUtil.h"
#include "AnimateManager.h"
#include "BossManager.h"
#include "AddJewelNode.h"

GameScene::~GameScene() {
	CC_SAFE_RELEASE(_arrowArray);
	CC_SAFE_RELEASE(_enemyArray);
	CC_SAFE_RELEASE(_arrowArrayRM);
	CC_SAFE_RELEASE(_enemyArrayRM);
	NotificationCenter::getInstance()->removeAllObservers(this);
	DIRECTOR->getEventDispatcher()->removeEventListenersForTarget(this);
}

Scene* GameScene::createScene(int level) {
	auto scene = Scene::create();
	scene->addChild(GameScene::createGameScene(level));
	return scene;
}

GameScene* GameScene::createGameScene(int level) {
	auto scene = new GameScene();
	if (scene && scene->initScene(level)) {
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return nullptr;
}

bool GameScene::initScene(int level) {
	if (!Layer::init()) return false;
	_level = level;
	_boss = nullptr;
	_isShoot = false;
	_airSpeed = CsvUtil::getInstance()->getValueForAB(DATAOPERATOR->getSelectBow(), ArrowAndBowProperty::flyspeed, ARROWANDBOWFILE_CSV_NAME).asInt();
	this->loadResourse();

	if (DATAOPERATOR->getMusicEnable())
		AUDIOENGINE->playBackgroundMusic(GAMESCENE_BGM_NAME, true);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::enemyDie), "enemy_die", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::enemyOver), "enemy_over", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::bossDie), "boss_death", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::gameWin), "game_win", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::gameOver), "game_over", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::card_Death), "Death", NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::card_Judgement), "Judgement", NULL);

	auto rootNode = CSLoader::createNode(GAMESCENE_CSB_NAME);
	this->addChild(rootNode);
	auto action = CSLoader::createTimeline(GAMESCENE_CSB_NAME);
	rootNode->runAction(action);
	action->gotoFrameAndPlay(0);

	_background = rootNode->getChildByName(BGLAYER);
	_panel = rootNode->getChildByName(PANELLAYER);
	_pause = rootNode->getChildByName(PAUSELAYER);

	_arrowArray = __Array::create();
	_enemyArray = __Array::create();
	_arrowArrayRM = __Array::create();
	_enemyArrayRM = __Array::create();
	CC_SAFE_RETAIN(_arrowArray);
	CC_SAFE_RETAIN(_enemyArray);
	CC_SAFE_RETAIN(_arrowArrayRM);
	CC_SAFE_RETAIN(_enemyArrayRM);

	auto wallNode = _background->getChildByName(WALLNODE)->getPositionX();
	_wallNode = wallNode;
	_manager = GameManager::createManager(_level, wallNode, this);
	this->addChild(_manager);

	//³õÊ¼»¯¹­
	auto pos = _background->getChildByName(BOWPOSNODE)->getPosition();
	_bow = Bow::createBow(pos, this);
	_background->addChild(_bow, 700);

	this->initPanel();
	this->initPause();
	this->updateLabel();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	DIRECTOR->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(GameScene::updateArray));
	this->schedule(schedule_selector(GameScene::collisionListener));

	return true;
}

void GameScene::initPanel() {
	auto levelLabel = _panel->getChildByName<Text *>(LEVELLABEL);
	levelLabel->setFontName(TEXTFONT_NAME);
	levelLabel->setString(StringUtils::format("Stage.%d", _level).c_str());

	auto pauseButton = _panel->getChildByName<Button *>(PAUSEBUTTON);
	pauseButton->addClickEventListener([=](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		this->pauseGame();
		_pause->setVisible(true);
	});

	_arrowState = ArrowState::NORMAL;
	auto fireArrowButton = _panel->getChildByName<Button *>(FIREARROWBUTTON);
	fireArrowButton->addClickEventListener([=](Ref *ref) {
		if (_manager->getCurrectMp() < 5) {
			if (DATAOPERATOR->getEffectEnable())
				AUDIOENGINE->playEffect(GOLDOVER_EFFECT_NAME);
		}
		else {
			if (DATAOPERATOR->getEffectEnable())
				AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
			if (_arrowState == ArrowState::FIRE) {
				_arrowState = ArrowState::NORMAL;
				this->unschedule("fire_arrow");
			}
			else {
				_arrowState = ArrowState::FIRE;
				this->schedule([=](float) {
					if (_manager->getCurrectMp() < 5)
						_arrowState = ArrowState::NORMAL;
				}, "fire_arrow");
			}
		}
		
	});
	auto freezeButton = _panel->getChildByName<Button *>(FREEZEBUTTON);
	freezeButton->addClickEventListener([=](Ref *ref) {
		if (_manager->getCurrectMp() < 100) {
			if (DATAOPERATOR->getEffectEnable())
				AUDIOENGINE->playEffect(GOLDOVER_EFFECT_NAME);
		}
		else {
			if (DATAOPERATOR->getEffectEnable())
				AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
			_manager->setCurrectMp(_manager->getCurrectMp() - 100);
			this->updateLabel();
			this->freezeMagic();
		}
	});
	auto lightingButton = _panel->getChildByName<Button *>(LIGHTINGBUTTON);
	lightingButton->addClickEventListener([=](Ref *ref) {
		if (_manager->getCurrectMp() < 100) {
			if (DATAOPERATOR->getEffectEnable())
				AUDIOENGINE->playEffect(GOLDOVER_EFFECT_NAME);
		}
		else {
			if (DATAOPERATOR->getEffectEnable())
				AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
			_manager->setCurrectMp(_manager->getCurrectMp() - 100);
			this->updateLabel();
			this->lightingMagic();
		}
	});

	this->updateLabel();
}

void GameScene::initPause() {
	auto resume = _pause->getChildByName<Button *>(RESUMEBUTTON);
	resume->addClickEventListener([=](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		this->resumeGame();
		_pause->setVisible(false);
	});

	auto retry = _pause->getChildByName<Button *>(RETRYBUTTON);
	retry->addClickEventListener([=](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		DIRECTOR->replaceScene(GameScene::createScene(_level));
	});

	auto back = _pause->getChildByName<Button *>(HOMEBUTTON);
	back->addClickEventListener([=](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		DIRECTOR->replaceScene(SelectScene::createScene());
	});

	this->upgradeGroup(Value("HP").asString());
	this->upgradeGroup(Value("MP").asString());
	this->upgradeGroup(Value("attack").asString());
	this->upgradeGroup(Value("shoot_speed").asString());
	this->upgradeGroup(Value("multarrow").asString());
	this->upgradeGroup(Value("airspeed").asString());
	this->upgradeGroup(Value("knock_back").asString());
	this->upgradeGroup(Value("range").asString());
}

void GameScene::upgradeGroup(std::string groupName) {
	auto label = _pause->getChildByName<Text *>(StringUtils::format("%s_Label", groupName.c_str()).c_str());
	label->setFontName(TEXTFONT_NAME);
	auto bar = _pause->getChildByName<LoadingBar *>(StringUtils::format("%s_Bar", groupName.c_str()).c_str());
	bar->setPercent(_bow->getProperty(groupName) * 5);
	auto button = _pause->getChildByName<Button *>(StringUtils::format("%s_Button", groupName.c_str()).c_str());
	button->addClickEventListener([=](Ref *) {
		if (!groupName.compare("HP")) {
			if (DATAOPERATOR->getJewel() < 100) {
				if (DATAOPERATOR->getEffectEnable())
					AUDIOENGINE->playEffect(GOLDOVER_EFFECT_NAME);
				return;
			}
			DATAOPERATOR->setJewel(DATAOPERATOR->getJewel() - 100);
			_manager->setCurrectHp(_manager->getCurrectHp() + 100);
		}
		else if (!groupName.compare("MP")) {
			if (DATAOPERATOR->getJewel() < 100) {
				if (DATAOPERATOR->getEffectEnable())
					AUDIOENGINE->playEffect(GOLDOVER_EFFECT_NAME);
				return;
			}
			DATAOPERATOR->setJewel(DATAOPERATOR->getJewel() - 100);
			_manager->setCurrectMp(_manager->getCurrectMp() + 100);
		}
		else {
			if (DATAOPERATOR->getGold() < 100) {
				if (DATAOPERATOR->getEffectEnable())
					AUDIOENGINE->playEffect(GOLDOVER_EFFECT_NAME);
				return;
			}
			DATAOPERATOR->setGold(DATAOPERATOR->getGold() - 100);
		}
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(STATEUPGRADE_EFFECT_NAME);
		_bow->setProperty(groupName, _bow->getProperty(groupName) + 1);
		bar->setPercent(_bow->getProperty(groupName) * 5);
		if (!groupName.compare("airspeed")) {
			_airSpeed++;
		}
		this->updateLabel();
	});
}

void GameScene::updateLabel() {
	auto jewelLabel = _panel->getChildByName<Text *>(JEWELLABEL);
	jewelLabel->setFontName(TEXTFONT_NAME);
	jewelLabel->setString(StringUtils::format("%d", DATAOPERATOR->getJewel()).c_str());

	auto goldLabel = _panel->getChildByName<Text *>(GOLDLABEL);
	goldLabel->setFontName(TEXTFONT_NAME);
	goldLabel->setString(StringUtils::format("%d", DATAOPERATOR->getGold()).c_str());

	auto progress = _panel->getChildByName(PROGRESS);
	_manager->setProgress(progress);

	auto statePanel = _panel->getChildByName(BLOODPANEL);
	auto bloodBar = statePanel->getChildByName<LoadingBar *>(BLOODBAR);
	auto magicBar = statePanel->getChildByName<LoadingBar *>(MAGICBAR);
	auto bloodLabel = statePanel->getChildByName<Text *>(BLOODLABEL);
	auto magicLabel = statePanel->getChildByName<Text *>(MAGICLABEL);

	bloodBar->setPercent((float)_manager->getCurrectHp() / DATAOPERATOR->getMaxHp() * 100);
	magicBar->setPercent((float)_manager->getCurrectMp() / DATAOPERATOR->getMaxMp() * 100);
	bloodLabel->setString(StringUtils::format("%d/%d", _manager->getCurrectHp(), DATAOPERATOR->getMaxHp()));
	magicLabel->setString(StringUtils::format("%d/%d", _manager->getCurrectMp(), DATAOPERATOR->getMaxMp()));
	bloodLabel->setFontName(TEXTFONT_NAME);
	magicLabel->setFontName(TEXTFONT_NAME);

	auto bg_2 = _background->getChildByName(BG_2);
	auto bg_3 = _background->getChildByName(BG_3);
	if (_manager->getCurrectHp() < DATAOPERATOR->getMaxHp() * 0.5f) {
		bg_2->setVisible(true);
		bg_3->setVisible(false);
	}
	else if (_manager->getCurrectHp() > 1000) {
		bg_2->setVisible(false);
		bg_3->setVisible(true);
	}
}

void GameScene::pauseGame() {
	_background->onExit();
	_manager->pause();
	this->pause();
}

void GameScene::resumeGame() {
	_background->onEnter();
	_manager->resume();
	this->resume();
}

void GameScene::enemyDie(Ref *sender) {
	int mp = dynamic_cast<__Integer *>(sender)->getValue();
	_manager->setCurrectMp(_manager->getCurrectMp() + mp);
	if (_manager->getCurrectMp() > DATAOPERATOR->getMaxMp())
		_manager->setCurrectMp(DATAOPERATOR->getMaxMp());
	this->updateLabel();
}

void GameScene::enemyOver(Ref *sender) {
	_boss = BossManager::getInstance()->getBoss(_level, _wallNode, this);
	if (_boss) {
		auto warningLayer = CSLoader::createNode(WARNINGLAYER_CSB_NAME);
		this->addChild(warningLayer);
		auto action = CSLoader::createTimeline(WARNINGLAYER_CSB_NAME);
		warningLayer->runAction(action);
		action->gotoFrameAndPlay(0, false);
	}
	_background->addChild(_boss);
}

void GameScene::bossDie(Ref *sender) {
	_isGetingJewel = false;
	this->unschedule("shooting");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::bossTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::bossTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::bossTouchEnded, this);
	DIRECTOR->getEventDispatcher()->removeAllEventListeners();
	DIRECTOR->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::gameWin(Ref *sender) {
	this->pauseGame();
	auto layer = GameWinLayer::createLayer(_level);
	this->addChild(layer);
}

void GameScene::gameOver(Ref *sender) {
	this->updateLabel();
	this->pauseGame();
	auto layer = GameOverLayer::create();
	this->addChild(layer);
}

void GameScene::card_Death(Ref *sender) {
	auto skeleton = Sprite::create("Game/skeleton.png");
	skeleton->setScale(0.01f);
	skeleton->setPosition(Vec2(SCREEN.width * 0.5, SCREEN.height * 0.5));
	this->addChild(skeleton);
	_background->onExit();
	auto scale = ScaleTo::create(1, 20);
	auto cf = CallFunc::create([=]() {
		skeleton->removeFromParent();
		for (int i = 0; i < _enemyArray->count(); i++) {
			auto enemy = dynamic_cast<Enemy *>(_enemyArray->getObjectAtIndex(i));
			enemy->hurt(200, 0);
		}
		if (_boss) _boss->hurt(200, 0);
		_background->onEnter();
	});
	auto seq = Sequence::create(scale, cf, NULL);
	skeleton->runAction(seq);
}

void GameScene::card_Judgement(Ref *sender) {
	if (_enemyArray->count() != 0) {
		auto num = (int)(CCRANDOM_0_1() * _enemyArray->count());
		auto enemy = dynamic_cast<Enemy *>(_enemyArray->getObjectAtIndex(num));
		if (enemy->getState() == EnemyState::DEATH) {
			this->card_Judgement(nullptr);
			return;
		}
		this->lightingMagicAnimate(enemy->getPosition());
		enemy->hurt(1000, 0);
	}
	else {
		if (_boss) {
			this->lightingMagicAnimate(_boss->getPosition());
			_boss->hurt(1000, 0);
		}
	}
	
}

Node* GameScene::getBackground() {
	return _background;
}

void GameScene::loadResourse() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BOWANDARROW_PLIST_NAME);
}

void GameScene::updateArray(float) {
	for (int i = 0; i < _arrowArrayRM->count(); i++) {
		_arrowArray->removeObject(_arrowArrayRM->getObjectAtIndex(i));
	}
	_arrowArrayRM->removeAllObjects();

	for (int i = 0; i < _enemyArrayRM->count(); i++) {
		_enemyArray->removeObject(_enemyArrayRM->getObjectAtIndex(i));
	}
	_enemyArrayRM->removeAllObjects();

	//log("_arrowArray %d", _arrowArray->count());
	//log("_enemyArray %d", _enemyArray->count());
}

void GameScene::collisionListener(float) {
	Arrow *arrow = nullptr;
	Enemy *enemy = nullptr;
	for (int i = 0; i < _enemyArray->count(); i++) {
		enemy = dynamic_cast<Enemy *>(_enemyArray->getObjectAtIndex(i));
		if (enemy->getPositionX() < SCREEN.width && enemy->getState() != EnemyState::DEATH) {
			for (int j = 0; j < _arrowArray->count(); j++) {
				arrow = dynamic_cast<Arrow *>(_arrowArray->getObjectAtIndex(j));
				if (enemy->getCollisionBox().containsPoint(arrow->getCollisionPoint())) {
					float var = (_arrowState == ArrowState::FIRE) ? 1.5f : 1;
					enemy->hurt(POWER_COEFFICIENT(_bow->getPower()) * var, KNOCKBACK_COEFFICIENT(_bow->getKnockback()));
					_arrowArrayRM->addObject(arrow);
					arrow->removeFromParent();
				}
			}
		}
	}

	if (_boss && _boss->getPositionX() < SCREEN.width && _boss->getState() != BossState::DEATH) {
		for (int j = 0; j < _arrowArray->count(); j++) {
			arrow = dynamic_cast<Arrow *>(_arrowArray->getObjectAtIndex(j));
			if (_boss->getCollisionBox().containsPoint(arrow->getCollisionPoint())) {
				float var = (_arrowState == ArrowState::FIRE) ? 1.5f : 1;
				_boss->hurt(POWER_COEFFICIENT(_bow->getPower()) * var, KNOCKBACK_COEFFICIENT(_bow->getKnockback()));
				_arrowArrayRM->addObject(arrow);
				arrow->removeFromParent();
			}
		}
	}
}

void GameScene::multpleArrows(int number) {
	Vec2 pos = _bow->getPosition();
	float angle = _angle;
	float range = RANGE_COEFFICIENT(_bow->getRange());
	if (_arrowState == ArrowState::FIRE)
		_manager->setCurrectMp(_manager->getCurrectMp() - 5);
	if (number % 2) {
		for (int i = 0; i < number; i++) {
			angle += i * range * pow(-1, i);
			auto arrow = Arrow::createArrow(pos, angle, _airSpeed, _arrowState, this);
			_background->addChild(arrow, 600);
			_arrowArray->addObject(arrow);
		}
	}
	else {
		for (int i = 0; i < number / 2; i++) {
			for (int j = 0; j < 2; j++) {
				float var = pow(-1, j) * (0.5 + i) * range;
				auto arrow = Arrow::createArrow(pos, angle + var, _airSpeed, _arrowState, this);
				_background->addChild(arrow, 600);
				_arrowArray->addObject(arrow);
			}
		}
	}
	this->updateLabel();
}

void GameScene::freezeMagic() {
	if (DATAOPERATOR->getEffectEnable())
		AUDIOENGINE->playEffect(FREEZEEFFECT);
	for (int i = 0; i < _enemyArray->count(); i++) {
		auto enemy = dynamic_cast<Enemy *>(_enemyArray->getObjectAtIndex(i));
		this->freezeMagicAnimate(enemy->getPosition());
		if (enemy->getState() != EnemyState::DEATH) enemy->setState(EnemyState::FREEZR);
	}
	if (_boss && _boss->getState() != BossState::DEATH) {
		this->freezeMagicAnimate(_boss->getPosition());
		_boss->setState(BossState::FREEZR);
	}
}

void GameScene::lightingMagic() {
	if (DATAOPERATOR->getEffectEnable())
		AUDIOENGINE->playEffect(LIGHTINGEFFECT);
	for (int i = 0; i < 15; i++) {
		this->lightingMagicAnimate(Vec2(150 + 600 * CCRANDOM_0_1(), 150 + 280 * CCRANDOM_0_1()));
	}
	for (int i = 0; i < _enemyArray->count(); i++) {
		auto enemy = dynamic_cast<Enemy *>(_enemyArray->getObjectAtIndex(i));
		if (enemy->getState() != EnemyState::DEATH) enemy->hurt(100, 0);
	}
	if (_boss && _boss->getState() != BossState::DEATH)
		_boss->hurt(100, 0);
}

void GameScene::freezeMagicAnimate(Vec2 v) {
	auto animate = AnimateManager::getInstance()->getAnimate("ice_piton_00%d.png", 8);
	auto freezeAnimate = Sprite::create();
	CallFunc *cb = CallFunc::create([=]() {
		freezeAnimate->removeFromParent();
	});
	auto seq = Sequence::create(animate, cb, NULL);
	freezeAnimate->runAction(seq);
	freezeAnimate->setPosition(v);
	this->addChild(freezeAnimate);
}

void GameScene::lightingMagicAnimate(Vec2 v) {
	Animate *animate = AnimateManager::getInstance()->getAnimate("light_strike_%d.png", 6, 5, 0.015f);
	auto animateSprite = Sprite::create();
	animateSprite->setPosition(v);
	CallFunc *cb = CallFunc::create([=]() {
		animateSprite->removeFromParent();
	});
	Sequence *seq = Sequence::create(animate, cb, NULL);
	animateSprite->runAction(seq);
	this->addChild(animateSprite);
}

bool GameScene::onTouchBegan(Touch *pTouch, Event *event) {
	this->setBowRotation(pTouch);
	this->schedule([=](float) {
		if (!_isShoot) {
			_isShoot = true;
			if (DATAOPERATOR->getEffectEnable())
				AUDIOENGINE->playEffect(ARROWSHOOT_EFFECT_NAME);
			this->multpleArrows(MULTARROW_COEFFICIENT(_bow->getMultple()));
			this->scheduleOnce([=](float) {
				_isShoot = false;
			}, SHOOTSPEED_COEFFICIENT(_bow->getSpeed()), "shoot_delay");
		}
	}, "shooting");
	return true;
}

void GameScene::onTouchMoved(Touch *pTouch, Event *event) {
	this->setBowRotation(pTouch);	
}

void GameScene::onTouchEnded(Touch *pTouch, Event *event) {
	this->setBowRotation(pTouch);
	this->unschedule("shooting");
}

void GameScene::setBowRotation(Touch *pTouch) {
	Vec2 v = pTouch->getLocation() - _bow->getPosition();
	_angle = CC_RADIANS_TO_DEGREES(v.getAngle(Vec2(1, 0)));
	if (_angle > 60) _angle = 60;
	if (_angle < -60) _angle = -60;
	_bow->setRotation(_angle);
}

bool GameScene::bossTouchBegan(Touch *pTouch, Event *event) {
	_fingerPoint = ParticleSystemQuad::create(FINGERPARTICLE_NAME);
	_fingerPoint->setPosition(pTouch->getLocation());
	this->addChild(_fingerPoint);
	return true;
}

void GameScene::bossTouchMoved(Touch *pTouch, Event *event) {
	_fingerPoint->setPosition(pTouch->getLocation());
	if (_isGetingJewel == false && _boss->getCollisionBox().containsPoint(pTouch->getLocation())) {
		_isGetingJewel = true;
		auto jewel = AddJewelNode::createNode(1);
		jewel->setPosition(pTouch->getLocation());
		this->addChild(jewel);
		this->scheduleOnce([=](float) {
			_isGetingJewel = false;
		}, 0.1f, "isGetingJewel");
	}
}

void GameScene::bossTouchEnded(Touch *pTouch, Event *event) {
	this->removeChild(_fingerPoint);
}