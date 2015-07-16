
#ifndef __MAP_CHOOSE_SCENE_H__
#define __MAP_CHOOSE_SCENE_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ConstUtil.h"
#include "BeachScene.h"
#include "SeaScene.h"
#include "SnowScene.h"
#include "Util.h"

USING_NS_CC;
USING_NS_CC_EXT;


const int  MAP_COUNT = 3;
const int TOUCH_DISTANCE = 50;


class MapChooseScene : public Layer,public ScrollViewDelegate
{
public:

    static Scene* createScene();
  
     bool init();        
 
    CREATE_FUNC(MapChooseScene);

private:
	Size visibleSize;

	Layer* _spritesContainer;
	void back(Object*);
     int currentPage;
     Point beginTouchPoint;
     ScrollView *scrollView;

	void singleTouchDown(Object* pSender,Control::EventType event);
	void addBackgroundSprite();

	void addScrollView();

	void scrollViewDidScroll(ScrollView* view);
    void scrollViewDidZoom(ScrollView* view);
    void scrollViewMoveOver(ScrollView* view);
	void adjustScrollView(float distance);
	void onTouchEnded(Touch*touch,Event *unused_event);
	bool onTouchBegan(Touch * touch,Event *unused_event);//¿ªÊ¼×´Ì¬
    void onTouchMoved(Touch *touch,Event *unused_event);//ÒÆ¶¯×´Ì¬


};



#endif



