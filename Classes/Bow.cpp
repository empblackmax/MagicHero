#include "Bow.h"
#include "CsvUtil.h"

Bow* Bow::createBow(Vec2 pos, Node *parent) {
	Bow *bow = new Bow();
	if (bow && bow->initBow(pos, parent)) {
		bow->autorelease();
		return bow;
	}
	CC_SAFE_DELETE(bow);
	return nullptr;
}

int Bow::getProperty(std::string property) {
	if (!property.compare("HP")) {
		return DATAOPERATOR->getMaxHp() / 100;
	}
	else if (!property.compare("MP")) {
		return DATAOPERATOR->getMaxMp() / 100;
	}
	else if (!property.compare("attack")) {
		return _power;
	}
	else if (!property.compare("shoot_speed")) {
		return _speed;
	}
	else if (!property.compare("multarrow")) {
		return _multple;
	}
	else if (!property.compare("airspeed")) {
		return _airSpeed;
	}
	else if (!property.compare("knock_back")) {
		return _knockBack;
	}
	else if (!property.compare("range")) {
		return _range;
	}
	else {
		return 0;
	}
}

void Bow::setProperty(std::string property, int value) {
	if (!property.compare("HP")) {
		DATAOPERATOR->setMaxHp(value * 100);
	}
	else if (!property.compare("MP")) {
		DATAOPERATOR->setMaxMp(value * 100);
	}
	else if (!property.compare("attack")) {
		_power = value;
	}
	else if (!property.compare("shoot_speed")) {
		_speed = value;
	}
	else if (!property.compare("multarrow")) {
		_multple = value;
	}
	else if (!property.compare("airspeed")) {
		_airSpeed = value;
	}
	else if (!property.compare("knock_back")) {
		_knockBack = value;
	}
	else if (!property.compare("range")) {
		_range = value;
	}
}

bool Bow::initBow(Vec2 pos, Node *parent) {
	this->setPosition(pos);
	_parent = parent;

	auto BowFrameName = CsvUtil::getInstance()->getValueForAB(DATAOPERATOR->getSelectBow(), ArrowAndBowProperty::BowFrameName, ARROWANDBOWFILE_CSV_NAME).asString();
	_showSprite = Sprite::createWithSpriteFrameName(BowFrameName.c_str());
	this->addChild(_showSprite);

	_power = CsvUtil::getInstance()->getValueForAB(DATAOPERATOR->getSelectBow(), ArrowAndBowProperty::power, ARROWANDBOWFILE_CSV_NAME).asInt();
	_speed = CsvUtil::getInstance()->getValueForAB(DATAOPERATOR->getSelectBow(), ArrowAndBowProperty::speed, ARROWANDBOWFILE_CSV_NAME).asInt();
	_range = CsvUtil::getInstance()->getValueForAB(DATAOPERATOR->getSelectBow(), ArrowAndBowProperty::range, ARROWANDBOWFILE_CSV_NAME).asInt();
	_multple = CsvUtil::getInstance()->getValueForAB(DATAOPERATOR->getSelectBow(), ArrowAndBowProperty::multarrow, ARROWANDBOWFILE_CSV_NAME).asInt();
	_airSpeed = CsvUtil::getInstance()->getValueForAB(DATAOPERATOR->getSelectBow(), ArrowAndBowProperty::flyspeed, ARROWANDBOWFILE_CSV_NAME).asInt();
	_knockBack = CsvUtil::getInstance()->getValueForAB(DATAOPERATOR->getSelectBow(), ArrowAndBowProperty::knockback, ARROWANDBOWFILE_CSV_NAME).asInt();

	return true;
}