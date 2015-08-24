#include "LevelButton.h"
#include "GameScene.h"

LevelButton* LevelButton::createButton(int level, Vec2 pos, Node *parent) {
	LevelButton *button = new LevelButton();
	if (button && button->initButton(level, pos, parent)) {
		button->autorelease();
		return button;
	}
	CC_SAFE_DELETE(button);
	return nullptr;
}

bool LevelButton::initButton(int level, Vec2 pos, Node *parent) {
	_level = level;
	_parent = parent;
	this->setPosition(pos);

	_showSprite = Sprite::create(LEVELBUTTON_BG_NAME);
	_showSprite->setScale(0.7f);
	this->addChild(_showSprite, 0);

	if (_level <= DATAOPERATOR->getUnlockLevel()) {
		_isLocked = false;
		auto levelLabel = Label::create(StringUtils::format("%d", _level), TEXTFONT_NAME, 36);
		this->addChild(levelLabel);
	}
	else {
		_isLocked = true;
		auto lock = Sprite::create(LEVELLOCKED_NAME);
		this->addChild(lock);
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LevelButton::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(LevelButton::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(LevelButton::onTouchEnded, this);
	DIRECTOR->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}

bool LevelButton::isTouchedInsert(Touch *pTouch) {
	auto touchPos = this->convertTouchToNodeSpace(pTouch);
	return _showSprite->getBoundingBox().containsPoint(touchPos) ? true : false;
}

bool LevelButton::onTouchBegan(Touch *pTouch, Event *event) {
	if (this->isTouchedInsert(pTouch)) {
		if (!_isLocked) {
			auto down = Sprite::create(TOUCHEDEFFECT_NAME);
			this->addChild(down, 1, "touched");
			return true;
		}
		else {
			if (DATAOPERATOR->getEffectEnable())
				AUDIOENGINE->playEffect(GOLDOVER_EFFECT_NAME);
			return false;
		}
	}
	return false;
}

void LevelButton::onTouchMoved(Touch *pTouch, Event *event) {
	if (!this->isTouchedInsert(pTouch)) {
		this->removeChildByName("touched");
	}
}

void LevelButton::onTouchEnded(Touch *pTouch, Event *event) {
	if (this->isTouchedInsert(pTouch)) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
		this->removeChildByName("touched");
		//ÇÐ»»µ½GameScene
		DIRECTOR->replaceScene(GameScene::createScene(_level));
	}
}