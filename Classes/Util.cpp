#include "Util.h"

Point Util::map2GL(const Point& ptMap, TMXTiledMap* map)
{
		Point ptUI;
		ptUI.x = ptMap.x * map->getTileSize().width;
		ptUI.y = (ptMap.y + 1)* map->getTileSize().height;

		Point ptGL = ptUI;
		ptGL.y = map->getContentSize().height - ptUI.y;
		return ptGL;
}

Point Util::GL2map(const Point& ptGL, TMXTiledMap* map)
{
		Point ptUI = ptGL;
		ptUI.y = map->getContentSize().height - ptGL.y;

		int x = ptUI.x / map->getTileSize().width;
		int y = ptUI.y / map->getTileSize().height;
		return ccp(x, y);
}
	
Vector<String*> Util::splitString(const char* srcStr, const char* sSep)
{
		Vector<String*> stringList ;  
  
		int size = strlen(srcStr);  
		String* str = String::create(srcStr);  
  
		int startIndex = 0;  
		int endIndex = 0;  
		endIndex = str->_string.find(sSep);  
  
		String* spliStr = NULL;  
  
		while(endIndex > 0) {  
			spliStr = CCString::create("");  
 			/* 截取字符串 */  
			spliStr->_string = str->_string.substr(startIndex, endIndex);  
  			/* 添加字符串到列表 */  
			stringList.pushBack(spliStr);  
  			/* 截取剩下的字符串 */  
			str->_string = str->_string.substr(endIndex + 1, size);  
			/* 查找下一个分隔符所在下标 */  
			endIndex = str->_string.find(sSep);  
		}  
		/* 剩下的字符串也添加进列表 */  
		if(str->_string.compare("") != 0) {  
			stringList.pushBack(String::create(str->_string));  
		}  
  
		return stringList; 
		
}
void Util::playRicherMusic(char* musicName,bool isLoop)
{
    bool music_on = UserDefault::getInstance()->getBoolForKey(MUSIC_ON_KEY,true);

	if(music_on)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(musicName, isLoop);
	}
}

void Util::playAudioEffect(const char* effectName,bool isLoop)
{
	bool music_on = UserDefault::getInstance()->getBoolForKey(MUSIC_ON_KEY,true);

	if(music_on)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(effectName, isLoop);
	}
}

void Util::playAudioEffectRandom(Vector<String*> effectVec, bool isLoop)
{
	playAudioEffect(effectVec.at(rand() % effectVec.size())->getCString(), isLoop);
}

void Util::stopAudioPlay()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

