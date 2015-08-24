#ifndef __DATA_OPERATOR_H__
#define __DATA_OPERATOR_H__

#include "Support.h"
USING_NS_CC;

#define DATAOPERATOR DataOperator::getInstance()

class DataOperator {
public:
	static DataOperator* getInstance();
	void setUnlockLevel(int unlockLevel);
	void setJewel(int jewel);
	void setGold(int gold);
	void setMaxHp(int maxHp);
	void setMaxMp(int maxMp);
	void setSelectBow(std::string selectedBow);
	void setDefault(bool unlock);
	void setSpeed1(bool unlock);
	void setSpeed2(bool unlock);
	void setSpeed3(bool unlock);
	void setMultple1(bool unlock);
	void setMultple2(bool unlock);
	void setMultple3(bool unlock);
	void setPower1(bool unlock);
	void setPower2(bool unlock);
	void setPower3(bool unlock);
	void setDemon(bool unlock);
	void setMusicEnable(bool musicEnable);
	void setEffectEnable(bool effectEnable);
private:
	void initData();
	//全局属性
	CC_SYNTHESIZE_READONLY(int, _unlockLevel, UnlockLevel);
	CC_SYNTHESIZE_READONLY(int, _jewel, Jewel);
	CC_SYNTHESIZE_READONLY(int, _gold, Gold);
	CC_SYNTHESIZE_READONLY(int, _maxHp, MaxHp);
	CC_SYNTHESIZE_READONLY(int, _maxMp, MaxMp);
	CC_SYNTHESIZE_READONLY(std::string, _selectedBow, SelectBow);
	//解锁状态
	CC_SYNTHESIZE_READONLY(bool, _default, Default);
	CC_SYNTHESIZE_READONLY(bool, _speed1, Speed1);
	CC_SYNTHESIZE_READONLY(bool, _speed2, Speed2);
	CC_SYNTHESIZE_READONLY(bool, _speed3, Speed3);
	CC_SYNTHESIZE_READONLY(bool, _multple1, Multple1);
	CC_SYNTHESIZE_READONLY(bool, _multple2, Multple2);
	CC_SYNTHESIZE_READONLY(bool, _multple3, Multple3);
	CC_SYNTHESIZE_READONLY(bool, _power1, Power1);
	CC_SYNTHESIZE_READONLY(bool, _power2, Power2);
	CC_SYNTHESIZE_READONLY(bool, _power3, Power3);
	CC_SYNTHESIZE_READONLY(bool, _demon, Demon);
	//设定状态
	CC_SYNTHESIZE_READONLY(bool, _musicEnable, MusicEnable);
	CC_SYNTHESIZE_READONLY(bool, _effectEnable, EffectEnable);
};

#endif