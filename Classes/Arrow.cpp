#include "Arrow.h"
#include "CsvUtil.h"
#include "GameScene.h"

Arrow* Arrow::createArrow(Vec2 pos, float angle, int flyspeed, ArrowState state, Node *parent) {
	auto arrow = new Arrow();
	if (arrow && arrow->initArrow(pos, angle, flyspeed, state, parent)) {
		arrow->autorelease();
		return arrow;
	}
	CC_SAFE_DELETE(arrow);
	return nullptr;
}

Vec2 Arrow::getCollisionPoint() {
	Rect rect = _showSprite->getBoundingBox();
	return this->convertToWorldSpace(Vec2(rect.getMaxX(), rect.getMidY()));
}

bool Arrow::initArrow(Vec2 pos, float angle, int flyspeed, ArrowState state, Node *parent) {
	this->setPosition(pos);
	this->setRotation(angle);
	_flyspeed = flyspeed;
	_parent = parent;
	_state = state;

	auto arrowFrameName = CsvUtil::getInstance()->getValueForAB(DATAOPERATOR->getSelectBow(), ArrowAndBowProperty::ArrowFrameName, ARROWANDBOWFILE_CSV_NAME).asString();
	_showSprite = Sprite::createWithSpriteFrameName(arrowFrameName.c_str());
	this->addChild(_showSprite);

	if (_state == ArrowState::FIRE) {
		auto fire = ParticleSystemQuad::create(FIREARROWPARTICLE_NAME);
		Rect rect = _showSprite->getBoundingBox();
		fire->setPosition(Vec2(rect.getMaxX(), rect.getMidY()));
		this->addChild(fire);
	}

	this->schedule([=](float) {
		this->setPosition(this->getPosition() + this->getNormalizedByAngle(angle) * AIRSPEED_COEFFICIENT(_flyspeed));
		if (this->getPositionX() > SCREEN.width + _showSprite->getContentSize().width * 0.5 || this->getPositionY() > SCREEN.height + _showSprite->getContentSize().height * 0.5 || this->getPositionY() < -_showSprite->getContentSize().width * 0.5) {
			auto scene = dynamic_cast<GameScene *>(_parent);
			scene->getArrowArrayRM()->addObject(this);
			this->removeFromParent();
		}
	}, "arrow_fly");
	return true;
}

Vec2 Arrow::getNormalizedByAngle(float angle) {
	auto randion = CC_DEGREES_TO_RADIANS(-angle);
	return Vec2(1, tan(randion)).getNormalized();
}