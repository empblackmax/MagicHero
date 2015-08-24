#include "MenuScene.h"
#include "SelectScene.h"
#include "CsvUtil.h"
#include "DataOperator.h"

Scene* MenuScene::createScene() {
	Scene *scene = Scene::create();
	scene->addChild(MenuScene::create());
	return scene;
}

bool MenuScene::init() {
	if (!Layer::init()) return false;


	if (USERDEFAULT->getBoolForKey(NEW_PLAYER_KEY, true)) {
		//玩家第一次进入游戏，做数据初始化操作
		USERDEFAULT->setIntegerForKey(UNLOCK_LEVEL_KEY, 1);
		USERDEFAULT->setIntegerForKey(JEWEL_KEY, 10000);
		USERDEFAULT->setIntegerForKey(GOLD_KEY, 100000);
		USERDEFAULT->setIntegerForKey(MAX_HP_KEY, 100);
		USERDEFAULT->setIntegerForKey(MAX_MP_KEY, 100);
		USERDEFAULT->setStringForKey(SELECTEDBOW_KEY, DEFAULT_BOW);

		USERDEFAULT->setBoolForKey(DEFAULT_BOW, true);
		USERDEFAULT->setBoolForKey(SPEED_1_BOW, false);
		USERDEFAULT->setBoolForKey(SPEED_2_BOW, false);
		USERDEFAULT->setBoolForKey(SPEED_3_BOW, false);
		USERDEFAULT->setBoolForKey(MULTPLE_1_BOW, false);
		USERDEFAULT->setBoolForKey(MULTPLE_2_BOW, false);
		USERDEFAULT->setBoolForKey(MULTPLE_3_BOW, false);
		USERDEFAULT->setBoolForKey(POWER_1_BOW, false);
		USERDEFAULT->setBoolForKey(POWER_2_BOW, false);
		USERDEFAULT->setBoolForKey(POWER_3_BOW, false);
		USERDEFAULT->setBoolForKey(DEMON_BOW, false);

		USERDEFAULT->setBoolForKey(MUSIC_ENABLE_KEY, true);
		USERDEFAULT->setBoolForKey(EFFECT_ENABLE_KEY, true);

		USERDEFAULT->setBoolForKey(NEW_PLAYER_KEY, false);
		USERDEFAULT->flush();
	}

	//初始化数据
	if (DATAOPERATOR->getMusicEnable() && !AUDIOENGINE->isBackgroundMusicPlaying())
		AUDIOENGINE->playBackgroundMusic(MENUSCENE_BGM_NAME, true);

	//_rootNode = CSLoader::createNode(MENUSCENE_CSB_NAME);
	_rootNode = CSLoader::createNode("MenuScene.csb");
	this->addChild(_rootNode);
	auto action = CSLoader::createTimeline(MENUSCENE_CSB_NAME);
	_rootNode->runAction(action);
	action->gotoFrameAndPlay(0, false);

	//初始化按钮
	this->initButton();

	return true;
}

void MenuScene::initButton() {
	auto startButton = _rootNode->getChildByName<Button *>(STARTBUTTON);
	startButton->addClickEventListener([](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		//跳转关卡选择界面
		DIRECTOR->replaceScene(SelectScene::createScene());
	});

	auto musicButton = _rootNode->getChildByName<Button *>(MUSICBUTTON);
	musicButton->addClickEventListener([](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		if (DATAOPERATOR->getMusicEnable()) {
			AUDIOENGINE->stopBackgroundMusic();
			DATAOPERATOR->setMusicEnable(false);
		}
		else {
			AUDIOENGINE->playBackgroundMusic(MENUSCENE_BGM_NAME, true);
			DATAOPERATOR->setMusicEnable(true);
		}
		
	});

	auto effectButton = _rootNode->getChildByName<Button *>(EFFECTBUTTON);
	effectButton->addClickEventListener([](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable()) {
			DATAOPERATOR->setEffectEnable(false);
		}
		else {
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
			DATAOPERATOR->setEffectEnable(true);
		}
	});
}