#include "BossManager.h"
#include "OrcBoss.h"
#include "WoodManBoss.h"
#include "WitchBoss.h"

static BossManager *manager = nullptr;

BossManager* BossManager::getInstance() {
	if (!manager) {
		manager = new BossManager();
	}
	return manager;
}

Boss* BossManager::getBoss(int level, int wallNode, Node *parent) {
	ValueMap fileMap = FileUtils::getInstance()->getValueMapFromFile(StringUtils::format("LevelSetting/Level_%02d.plist", level).c_str());
	auto bossName = fileMap.at("boss_name").asString();
	if (!bossName.compare("Orc")) {
		return OrcBoss::createBoss(wallNode, parent);
	}
	else if (!bossName.compare("WoodMan")) {
		return WoodManBoss::createBoss(wallNode, parent);
	}
	else if (!bossName.compare("Witch")) {
		return WitchBoss::createBoss(wallNode, parent);
	}
	return nullptr;
}