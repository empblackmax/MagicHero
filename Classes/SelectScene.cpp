#include "SelectScene.h"
#include "MenuScene.h"
#include "BowButton.h"
#include "LevelButton.h"
#include "GameScene.h"

Scene* SelectScene::createScene() {
	auto scene = Scene::create();
	scene->addChild(SelectScene::create());
	return scene;
}

void SelectScene::unselectBowButton() {
	std::string nameList[11] = BOW_LIST;
	for (int i = 0; i < 11; i++) {
		auto button = dynamic_cast<BowButton *>(_bowLayer->getChildByName(nameList[i]));
		button->unselect();
	}
}

bool SelectScene::init() {
	if (!Layer::init()) return false;

	if (DATAOPERATOR->getMusicEnable())
		AUDIOENGINE->playBackgroundMusic(MENUSCENE_BGM_NAME, true);

	auto rootNode = CSLoader::createNode(SELECTSCENE_CSB_NAME);
	this->addChild(rootNode);

	_jewel = rootNode->getChildByName<Text *>(JEWELTEXT);
	_gold = rootNode->getChildByName<Text *>(GOLDTEXT);
	_jewel->setFontName(TEXTFONT_NAME);
	_gold->setFontName(TEXTFONT_NAME);
	this->updateLabel();

	_bowLayer = rootNode->getChildByName(BowSELECTLAYER);
	_levelLayer = rootNode->getChildByName(LEVELSELECTLAYER);
	_levelLayer->setPosition(Vec2(0, 800));
	this->initBowLayer();
	this->initLevelLayer();

	auto levelSelectButton = rootNode->getChildByName<Button *>(LEVELSELECTBUTTON);
	levelSelectButton->addClickEventListener([=](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		_levelLayer->setPosition(Vec2(0, 0));
		_levelLayer->setVisible(true);
		_levelLayer->onEnter();
		_bowLayer->onExit();
	});

	auto closeButton = rootNode->getChildByName<Button *>(CLOSE);
	closeButton->addClickEventListener([](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		DIRECTOR->replaceScene(MenuScene::createScene());
	});

	auto continueButton = rootNode->getChildByName<Button *>(CONTINUE);
	continueButton->addClickEventListener([](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		//切换到最新关卡
		DIRECTOR->replaceScene(GameScene::createScene(DATAOPERATOR->getUnlockLevel()));
	});
	return true;
}

void SelectScene::updateLabel() {
	_jewel->setString(Value(DATAOPERATOR->getJewel()).asString());
	_gold->setString(Value(DATAOPERATOR->getGold()).asString());
}

void SelectScene::initBowLayer() {
	std::string nameList[11] = BOW_LIST;
	__Array *preSkill[11] = PRESKILLS_LIST;
	Vec2 v[11] = ICON_POSLIST;
	preSkill[10]->addObject(__String::create(MULTPLE_3_BOW));
	preSkill[10]->addObject(__String::create(SPEED_3_BOW));
	preSkill[10]->addObject(__String::create(POWER_3_BOW));
	for (int i = 0; i < 11; i++) {
		auto button = BowButton::createButton(nameList[i], v[i], preSkill[i], this);
		button->setGlobalZOrder(10);
		_bowLayer->addChild(button, 0, nameList[i]);
	}
}

void SelectScene::initLevelLayer() {
	auto bowSelectLayer = _levelLayer->getChildByName<Button *>(BOWSELECTBUTTON);
	bowSelectLayer->addClickEventListener([=](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		_levelLayer->setPosition(Vec2(0, 800));
		_levelLayer->setVisible(false);
		_levelLayer->onExit();
		_bowLayer->onEnter();
	});

	for (int i = 0; i < 12; i++) {
		Vec2 v = Vec2(120 * (i % 6) + 100, 320 - 120 * (i / 6));
		auto button = LevelButton::createButton(i + 1, v, this);
		_levelLayer->addChild(button);
	}
}