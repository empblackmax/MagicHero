#include "GameOverLayer.h"
#include "SelectScene.h"

bool GameOverLayer::init() {
	if (!Layer::init()) return false;

	if (DATAOPERATOR->getEffectEnable())
		AUDIOENGINE->playBackgroundMusic(GAMEOVER_BGM_NAME);

	auto rootNode = CSLoader::createNode(GAMEOVERLAYER_CSB_NAME);
	this->addChild(rootNode);
	auto action = CSLoader::createTimeline(GAMEOVERLAYER_CSB_NAME);
	rootNode->runAction(action);
	action->gotoFrameAndPlay(0, false);

	auto back = rootNode->getChildByName<Button *>(RETURNBUTTON);
	back->addClickEventListener([=](Ref *ref) {
		DIRECTOR->replaceScene(SelectScene::createScene());
	});

	return true;
}