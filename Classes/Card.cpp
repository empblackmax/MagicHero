#include "Card.h"
#include "CsvUtil.h"

Card* Card::createCard(Vec2 pos, Node *parent) {
	auto card = new Card();
	if (card && card->initCard(pos, parent)) {
		card->autorelease();
		return card;
	}
	CC_SAFE_DELETE(card);
	return nullptr;
}

bool Card::initCard(Vec2 pos, Node *parent) {
	this->setPosition(pos);

	auto rootNode = CSLoader::createNode(CARD_CSB_NAME);
	this->addChild(rootNode);
	auto action = CSLoader::createTimeline(CARD_CSB_NAME);
	rootNode->runAction(action);
	action->gotoFrameAndPlay(0);

	auto image = rootNode->getChildByName<Sprite *>(CARDIMAGE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(CARD_PLIST_NAME);
	auto cardID = (int)(CCRANDOM_0_1() * 2);
	auto cardName = CsvUtil::getInstance()->getValueForCard(cardID, CARD_CSV_NAME).asString();
	image->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s.png", cardName.c_str())));

	auto button = rootNode->getChildByName<Button *>(CARDTOUCH_BUTTON);
	button->addClickEventListener([=](Ref *ref) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		this->removeFromParent();
		auto click = ParticleSystemQuad::create(CARD_PARTICLE_NAME);
		click->setPosition(pos);
		parent->addChild(click);

		NotificationCenter::getInstance()->postNotification(cardName);
	});

	return true;
}
