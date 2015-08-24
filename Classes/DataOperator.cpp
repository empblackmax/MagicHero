#include "DataOperator.h"

static DataOperator *data = nullptr;
DataOperator* DataOperator::getInstance() {
	if (data == nullptr) {
		data = new DataOperator();
		data->initData();
	}
	return data;
}

void DataOperator::initData() {
	//初始化类数据
	_unlockLevel = USERDEFAULT->getIntegerForKey(UNLOCK_LEVEL_KEY);
	_jewel = USERDEFAULT->getIntegerForKey(JEWEL_KEY);
	_gold = USERDEFAULT->getIntegerForKey(GOLD_KEY);
	_maxHp = USERDEFAULT->getIntegerForKey(MAX_HP_KEY);
	_maxMp = USERDEFAULT->getIntegerForKey(MAX_MP_KEY);
	_selectedBow = USERDEFAULT->getStringForKey(SELECTEDBOW_KEY);

	_default = USERDEFAULT->getBoolForKey(DEFAULT_BOW);
	_speed1 = USERDEFAULT->getBoolForKey(SPEED_1_BOW);
	_speed2 = USERDEFAULT->getBoolForKey(SPEED_2_BOW);
	_speed3 = USERDEFAULT->getBoolForKey(SPEED_3_BOW);
	_multple1 = USERDEFAULT->getBoolForKey(MULTPLE_1_BOW);
	_multple2 = USERDEFAULT->getBoolForKey(MULTPLE_2_BOW);
	_multple3 = USERDEFAULT->getBoolForKey(MULTPLE_3_BOW);
	_power1 = USERDEFAULT->getBoolForKey(POWER_1_BOW);
	_power2 = USERDEFAULT->getBoolForKey(POWER_2_BOW);
	_power3 = USERDEFAULT->getBoolForKey(POWER_3_BOW);
	_demon = USERDEFAULT->getBoolForKey(DEMON_BOW);

	_musicEnable = USERDEFAULT->getBoolForKey(MUSIC_ENABLE_KEY);
	_effectEnable = USERDEFAULT->getBoolForKey(EFFECT_ENABLE_KEY);
}

void DataOperator::setUnlockLevel(int unlockLevel) {
	_unlockLevel = unlockLevel;
	USERDEFAULT->setIntegerForKey(UNLOCK_LEVEL_KEY, _unlockLevel);
	USERDEFAULT->flush();
}


void DataOperator::setJewel(int jewel) {
	_jewel = jewel;
	USERDEFAULT->setIntegerForKey(JEWEL_KEY, _jewel);
	USERDEFAULT->flush();
}

void DataOperator::setGold(int gold) {
	_gold = gold;
	USERDEFAULT->setIntegerForKey(GOLD_KEY, _gold);
	USERDEFAULT->flush();
}

void DataOperator::setMaxHp(int maxHp) {
	_maxHp = maxHp;
	USERDEFAULT->setIntegerForKey(MAX_HP_KEY, _maxHp);
	USERDEFAULT->flush();
}

void DataOperator::setMaxMp(int maxMp) {
	_maxMp = maxMp;
	USERDEFAULT->setIntegerForKey(MAX_MP_KEY, _maxMp);
	USERDEFAULT->flush();
}

void DataOperator::setSelectBow(std::string selectedBow) {
	_selectedBow = selectedBow;
	USERDEFAULT->setStringForKey(SELECTEDBOW_KEY, _selectedBow);
	USERDEFAULT->flush();
}

void DataOperator::setDefault(bool unlock) {
	_default = unlock;
	USERDEFAULT->setBoolForKey(DEFAULT_BOW, _default);
	USERDEFAULT->flush();
}

void DataOperator::setSpeed1(bool unlock) {
	_speed1 = unlock;
	USERDEFAULT->setBoolForKey(SPEED_1_BOW, _speed1);
	USERDEFAULT->flush();
}

void DataOperator::setSpeed2(bool unlock) {
	_speed2 = unlock;
	USERDEFAULT->setBoolForKey(SPEED_2_BOW, _speed2);
	USERDEFAULT->flush();
}

void DataOperator::setSpeed3(bool unlock) {
	_speed3 = unlock;
	USERDEFAULT->setBoolForKey(SPEED_3_BOW, _speed3);
	USERDEFAULT->flush();
}

void DataOperator::setMultple1(bool unlock) {
	_multple1 = unlock;
	USERDEFAULT->setBoolForKey(MULTPLE_1_BOW, _multple1);
	USERDEFAULT->flush();
}

void DataOperator::setMultple2(bool unlock) {
	_multple2 = unlock;
	USERDEFAULT->setBoolForKey(MULTPLE_2_BOW, _multple2);
	USERDEFAULT->flush();
}

void DataOperator::setMultple3(bool unlock) {
	_multple3 = unlock;
	USERDEFAULT->setBoolForKey(MULTPLE_3_BOW, _multple3);
	USERDEFAULT->flush();
}

void DataOperator::setPower1(bool unlock) {
	_power1 = unlock;
	USERDEFAULT->setBoolForKey(POWER_1_BOW, _power1);
	USERDEFAULT->flush();
}

void DataOperator::setPower2(bool unlock) {
	_power2 = unlock;
	USERDEFAULT->setBoolForKey(POWER_2_BOW, _power2);
	USERDEFAULT->flush();
}

void DataOperator::setPower3(bool unlock) {
	_power3 = unlock;
	USERDEFAULT->setBoolForKey(POWER_3_BOW, _power3);
	USERDEFAULT->flush();
}

void DataOperator::setDemon(bool unlock) {
	_demon = unlock;
	USERDEFAULT->setBoolForKey(DEMON_BOW, _demon);
	USERDEFAULT->flush();
}

void DataOperator::setMusicEnable(bool musicEnable) {
	_musicEnable = musicEnable;
	USERDEFAULT->setBoolForKey(MUSIC_ENABLE_KEY, _musicEnable);
	USERDEFAULT->flush();
}

void DataOperator::setEffectEnable(bool effectEnable) {
	_effectEnable = effectEnable;
	USERDEFAULT->setBoolForKey(EFFECT_ENABLE_KEY, _effectEnable);
	USERDEFAULT->flush();
}