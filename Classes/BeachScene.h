#ifndef __Beach_SCENE_H__
#define __Beach_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ConstUtil.h"
#include "GameBaseScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BeachScene: public GameBaseScene
{
public:
    static Scene* createScene();
	 void addMap();
	 void initTiledGrid();
	 void initPropTiledID();
    virtual bool init();  
   
	CREATE_FUNC(BeachScene);

private:

};

#endif