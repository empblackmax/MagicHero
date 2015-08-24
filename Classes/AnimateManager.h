#ifndef __ANIMATE_MANAGER_H__
#define __ANIMATE_MANAGER_H__

#include "Support.h"
USING_NS_CC;

class AnimateManager {
public:
	static AnimateManager* getInstance();
	void loadReourse();
	Animate* getAnimate(const char *frameName, int frameCount, int loop = 1, float Delay = 0.08);
};

#endif