#include "BowButton.h"
#include "SelectScene.h"

BowButton* BowButton::createButton(std::string bowName, Vec2 pos, __Array *preSkill, Node *parent) {
	BowButton* button = new BowButton();
	if (button && button->initButton(bowName, pos, preSkill, parent)) {
		button->autorelease();
		return button;
	}
	CC_SAFE_DELETE(button);
	return nullptr;
}

BowButton::~BowButton() {
	CC_SAFE_RELEASE(_selectShade);
	CC_SAFE_RELEASE(_up);
	CC_SAFE_RELEASE(_down);
	CC_SAFE_RELEASE(_lock);
	CC_SAFE_RELEASE(_preSkill);
}

void BowButton::unlock() {
	_state = BowButtonState::UNLOCK_SELECTED;
	_showSprite->setSpriteFrame(_up);
	USERDEFAULT->setBoolForKey(_bowName.c_str(), true);
	this->select();
	AUDIOENGINE->stopAllEffects();
	if (DATAOPERATOR->getEffectEnable())
		AUDIOENGINE->playEffect(STATEUPGRADE_EFFECT_NAME);
}

void BowButton::select() {
	if (DATAOPERATOR->getEffectEnable())
		AUDIOENGINE->playEffect(CLICKEFFECT_NAME);
	auto parent = dynamic_cast<SelectScene *>(_parent);
	parent->unselectBowButton();
	this->removeChildByName("selectShade");
	DATAOPERATOR->setSelectBow(_bowName);
	_state = BowButtonState::UNLOCK_SELECTED;
}

void BowButton::unselect() {
	if (_state == BowButtonState::UNLOCK_SELECTED) {
		this->addChild(_selectShade, 1, "selectShade");
		_state = BowButtonState::UNLOCK_UNSELECTED;
	}
}

bool BowButton::initButton(std::string bowName, Vec2 pos, __Array *preSkill, Node *parent) {
	this->setPosition(pos);
	_bowName = bowName;
	_preSkill = preSkill;
	_parent = parent;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BOWBUTTON_PLIST_NAME);
	_selectShade = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(UNSELECTICON_NAME));
	_up = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s_icon.png", bowName.c_str()).c_str());
	_down = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s_icon_down.png", bowName.c_str()).c_str());
	_lock = SpriteFrameCache::getInstance()->getSpriteFrameByName(LOCKEDICON_NAME);
	CC_SAFE_RETAIN(_selectShade);
	CC_SAFE_RETAIN(_up);
	CC_SAFE_RETAIN(_down);
	CC_SAFE_RETAIN(_lock);
	CC_SAFE_RETAIN(_preSkill);

	if (!USERDEFAULT->getBoolForKey(bowName.c_str())) {
		_state = BowButtonState::LOCKED;
		_showSprite = Sprite::createWithSpriteFrame(_lock);
	}
	else if (DATAOPERATOR->getSelectBow().compare(bowName.c_str()) == 0) {
		_state = BowButtonState::UNLOCK_SELECTED;
		_showSprite = Sprite::createWithSpriteFrame(_up);
	}
	else {
		_state = BowButtonState::UNLOCK_UNSELECTED;
		_showSprite = Sprite::createWithSpriteFrame(_up);
		this->addChild(_selectShade, 1, "selectShade");
	}
	this->addChild(_showSprite, 0);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(BowButton::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(BowButton::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(BowButton::onTouchEnded, this);
	DIRECTOR->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool BowButton::isUpgradeEnable() {
	bool flag = true;
	for (int i = 0; i < _preSkill->count(); i++) {
		if (!USERDEFAULT->getBoolForKey(dynamic_cast<__String *>(_preSkill->getObjectAtIndex(i))->getCString()))
			flag = false;
	}
	return flag;
}

bool BowButton::isTouchedInsert(Touch *pTouch) {
	Vec2 touchPos = pTouch->getLocation();
	Vec2 nodePos = this->convertToNodeSpace(touchPos);
	if (Rect(-_showSprite->getContentSize().width * 0.5, -_showSprite->getContentSize().height * 0.5, _showSprite->getContentSize().width, _showSprite->getContentSize().height).containsPoint(nodePos)) {
		return true;
	}
	return false;
}

bool BowButton::onTouchBegan(Touch *pTouch, Event *event) {
	if (this->isTouchedInsert(pTouch)) {
		if (_state != BowButtonState::LOCKED) 
			_showSprite->setSpriteFrame(_down);
		return true;
	}
	return false;
}

void BowButton::onTouchMoved(Touch *pTouch, Event *event) {
	if (!this->isTouchedInsert(pTouch)) {
		_showSprite->setSpriteFrame(_up);
	}
}

void BowButton::onTouchEnded(Touch *pTouch, Event *event) {
	int unlockJewel = 250;
	if (this->isTouchedInsert(pTouch)) {
		switch (_state) {
		case BowButtonState::LOCKED:
			if (DATAOPERATOR->getJewel() > unlockJewel && this->isUpgradeEnable()) {
				DATAOPERATOR->setJewel(DATAOPERATOR->getJewel() - unlockJewel);
				auto parent = dynamic_cast<SelectScene *>(_parent);
				parent->updateLabel();
				this->unlock();
			}
			else {
				if (DATAOPERATOR->getEffectEnable())
					AUDIOENGINE->playEffect(GOLDOVER_EFFECT_NAME);
			}
			break;
		case BowButtonState::UNLOCK_UNSELECTED:
			this->select();
			_showSprite->setSpriteFrame(_up);
			break;
		case BowButtonState::UNLOCK_SELECTED:
			_showSprite->setSpriteFrame(_up);
			break;
		default:
			break;
		}
	}
}