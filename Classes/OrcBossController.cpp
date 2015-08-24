#include "OrcBossController.h"
#include "Boss.h"

void OrcBossController::attack() {
	this->unschedule("enemy_run");
	_armature->getAnimation()->play("attack");
	this->schedule([=](float) {
		if (DATAOPERATOR->getEffectEnable())
			AUDIOENGINE->playEffect(WALLBEHIT_EFFECT_NAME);
		NotificationCenter::getInstance()->postNotification("enemy_attack", __Integer::create(_boss->getAttack()));
		if (_boss->getPositionX() > _wallNode) {
			_boss->setState(BossState::RUN);
		}
	}, 1, "enemy_attack");
}