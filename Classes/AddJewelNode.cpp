#include "AddJewelNode.h"

AddJewelNode* AddJewelNode::createNode(int count) {
	AddJewelNode *node = new AddJewelNode();
	if (node && node->initNode(count)) {
		node->autorelease();
		return node;
	}
	CC_SAFE_DELETE(node);
	return nullptr;
}

bool AddJewelNode::initNode(int count) {
	auto icon = Sprite::create(JEWELICON_NAME);
	icon->setAnchorPoint(Vec2(1, 0.5));
	icon->setScale(0.5);
	this->addChild(icon);
	int num = count;
	auto number = Text::create(StringUtils::format("%d", num).c_str(), TEXTFONT_NAME, 20);
	number->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(number);

	if (USERDEFAULT->getBoolForKey(EFFECT_ENABLE_KEY)) {
		AUDIOENGINE->playEffect(GETITEM_EFFECT_NAME);
	}
	
	MoveBy *moveBy = MoveBy::create(1, Vec2(0, 50));
	FadeOut *out = FadeOut::create(1);
	CallFunc *cb = CallFunc::create([=]() {
		this->removeFromParent();
	});
	Spawn *spawn = Spawn::create(moveBy, out, NULL);
	Sequence *seq = Sequence::create(spawn, cb, NULL);
	this->runAction(seq);

	return true;
}