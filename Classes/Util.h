#ifndef __UTIL_H__
#define __UTIL_H__

#define winSize Director::getInstance()->getWinSize()
#include "cocos2d.h"
#include "LanguageString.h"
#include "ConstUtil.h"
USING_NS_CC;

class Util
{
public:
    static Point map2GL(const Point& ptMap, TMXTiledMap* map);
    static Point GL2map(const Point& ptGL, TMXTiledMap* map);
	static Vector<String*> splitString(const char* srcStr, const char* sSep);
	static void playRicherMusic(char* musicName,bool isLoop);
	static void playAudioEffect(const char* effectName,bool isLoop);
	static void playAudioEffectRandom(Vector<String*> effectVec, bool isLoop);
	static void stopAudioPlay();
};


#endif