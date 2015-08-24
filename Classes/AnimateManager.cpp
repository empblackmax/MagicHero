#include "AnimateManager.h"

static AnimateManager* manager = nullptr;

AnimateManager* AnimateManager::getInstance() {
	if (manager == nullptr) {
		manager = new AnimateManager();
		manager->loadReourse();
	}
	return manager;
}

void AnimateManager::loadReourse() {
	for (int i = 0; i < 8; i++) {
		const char *plistName = __String::createWithFormat("Plist/monster%d.plist", i + 1)->getCString();
		const char *textureName = __String::createWithFormat("Plist/monster%d.png", i + 1)->getCString();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistName, textureName);
	}
	for (int i = 0; i < 4; i++) {
		const char *plistName = __String::createWithFormat("Plist/magic%d.plist", i + 1)->getCString();
		const char *textureName = __String::createWithFormat("Plist/magic%d.png", i + 1)->getCString();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistName, textureName);
	}
}

Animate* AnimateManager::getAnimate(const char *frameName, int frameCount, int loop, float delay) {
	Vector<SpriteFrame *> frames;
	SpriteFrame *frame = nullptr;
	for (int i = 0; i < frameCount; i++) {
		//log("%s", StringUtils::format(frameName, i + 1));
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(frameName, i + 1));
		if (frame == nullptr) break;
		frames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(frames);
	animation->setDelayPerUnit(delay);
	animation->setLoops(loop);
	return Animate::create(animation);
}