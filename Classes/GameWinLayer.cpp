#include "GameWinLayer.h"
#include "GameScene.h"
#include "SelectScene.h"

GameWinLayer* GameWinLayer::createLayer(int level) {
	auto layer = new GameWinLayer();
	if (layer && layer->initLayer(level)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool GameWinLayer::initLayer(int level) {
	if (!Layer::init()) return false;

	if (DATAOPERATOR->getUnlockLevel() == level)
		DATAOPERATOR->setUnlockLevel(level + 1);

	if (DATAOPERATOR->getEffectEnable())
		AUDIOENGINE->playBackgroundMusic(GAMEWIN_BGM_NAME);

	auto rootNode = CSLoader::createNode(GAMEWINLAYER_CSB_NAME);
	this->addChild(rootNode);
	auto action = CSLoader::createTimeline(GAMEWINLAYER_CSB_NAME);
	rootNode->runAction(action);
	action->gotoFrameAndPlay(0, false);

	auto text = rootNode->getChildByName<Text *>(WIN_TEXT);
	text->setFontName(TEXTFONT_NAME);

	auto resume = rootNode->getChildByName<Button *>(WIN_NEXTBUTTON);
	resume->addClickEventListener([=](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		DIRECTOR->replaceScene(GameScene::createScene(level + 1));
	});

	auto retry = rootNode->getChildByName<Button *>(WIN_RETRYBUTTON);
	retry->addClickEventListener([=](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		DIRECTOR->replaceScene(GameScene::createScene(level));
	});

	auto back = rootNode->getChildByName<Button *>(WIN_HOMEBUTTON);
	back->addClickEventListener([=](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		DIRECTOR->replaceScene(SelectScene::createScene());
	});

	return true;
}