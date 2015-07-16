#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__
#include "cocos2d.h"


#include "ConstUtil.h"
#include "MenuScene.h"
USING_NS_CC;


const  double MOVE_SPLEED  = 0.5f;
const int ONE_SECOND = 1;


class SplashScene : public Layer
{
public:

    static Scene* createScene();
  
    virtual bool init();        
   
	void moveKeSpriteToLeft();
	void moveMaiSpriteToLeft();
	void initMoveSprite();
	void startMoveSprite(float dt);
	void gotoMenuScene();
	void spriteFadeOut();
    CREATE_FUNC(SplashScene);

private:
	
	Sprite* mai_Sprite ;
	Sprite* ke_Sprite ;
	Sprite* ji_Sprite;
	Sprite* cheng_Sprite;
	Size visibleSize;
	Size spriteSize;

};

#endif
