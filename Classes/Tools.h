#ifndef __Tools_h__
#define __Tools_h__

#define SCREEN Director::getInstance()->getWinSize()
#define SET_POSITION(_x, _y) ccp(SCREEN.width * _x, SCREEN.height * _y)
#define	DIRECTOR Director::getInstance()
#define AUDIOENGINE SimpleAudioEngine::getInstance()
#define USERDEFAULT UserDefault::getInstance()


#endif
