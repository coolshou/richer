#include "SplashScene.h"


Scene* SplashScene::createScene()
{
	auto scene = Scene::create();

    auto layer = SplashScene::create();

    scene->addChild(layer);

    return scene;

}
  
bool SplashScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
	visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	initMoveSprite();
	scheduleOnce(schedule_selector(SplashScene::startMoveSprite), ONE_SECOND);  

    return true;
}

void SplashScene::startMoveSprite(float dt)
{
	MoveBy* moveChengToLeft1 = MoveBy::create(MOVE_SPLEED,ccp(-spriteSize.width,0));
	cheng_Sprite->runAction(moveChengToLeft1);

	MoveBy* moveJiToright = MoveBy::create(MOVE_SPLEED,ccp(spriteSize.width,0));

	CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(SplashScene::moveKeSpriteToLeft, this));

	ji_Sprite->runAction(Sequence::create(moveJiToright,callFunc,NULL));

}

void SplashScene::initMoveSprite()
{
	 mai_Sprite = Sprite::create(MAI_IMAGE);
	 ke_Sprite = Sprite::create(KE_IMAGE);
	 ji_Sprite = Sprite::create(JI_IMAGE);
	 cheng_Sprite = Sprite::create(CHENG_IMAGE);

	spriteSize = mai_Sprite->getContentSize();

	mai_Sprite->setPosition(ccp(visibleSize.width/2 - (2 *spriteSize.width),visibleSize.height/2));
	ke_Sprite->setPosition(ccp(visibleSize.width/2 -  spriteSize.width,visibleSize.height/2));
	ji_Sprite->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	cheng_Sprite->setPosition(ccp(visibleSize.width/2 + spriteSize.width,visibleSize.height/2));

	mai_Sprite->setAnchorPoint(ccp(0,0.5));
	ke_Sprite->setAnchorPoint(ccp(0,0.5));
	ji_Sprite->setAnchorPoint(ccp(0,0.5));
	cheng_Sprite->setAnchorPoint(ccp(0,0.5));

	this->addChild(mai_Sprite);
	this->addChild(ke_Sprite);
	this->addChild(ji_Sprite);
	this->addChild(cheng_Sprite);
}

   
void SplashScene::moveKeSpriteToLeft()
{
	MoveBy* moveChengToLeft2 = MoveBy::create(MOVE_SPLEED,ccp(-spriteSize.width,0));
	cheng_Sprite->runAction(moveChengToLeft2);

	MoveBy* ke_Sprite_MoveBy = MoveBy::create(MOVE_SPLEED,ccp(spriteSize.width,0));
	CallFunc* callFunc2 = CallFunc::create(CC_CALLBACK_0(SplashScene::moveMaiSpriteToLeft, this));
	ke_Sprite->runAction(Sequence::create(ke_Sprite_MoveBy,callFunc2,NULL));

}
void SplashScene::moveMaiSpriteToLeft()
{
	MoveBy* moveChengToLeft3 = MoveBy::create(MOVE_SPLEED,ccp(-spriteSize.width,0));
	cheng_Sprite->runAction(moveChengToLeft3);

	MoveBy* mai_Sprite_MoveBy = MoveBy::create(MOVE_SPLEED,ccp(spriteSize.width,0));
	CallFunc* callFunc3 = CallFunc::create(CC_CALLBACK_0(SplashScene::spriteFadeOut, this));
	mai_Sprite->runAction(Sequence::create(mai_Sprite_MoveBy,callFunc3,NULL));
}

void SplashScene:: spriteFadeOut()
{
	FadeOut* fadeOut1 = FadeOut::create(ONE_SECOND*2);
	FadeOut* fadeOut2 = FadeOut::create(ONE_SECOND*2);
	FadeOut* fadeOut3 = FadeOut::create(ONE_SECOND*2);
	FadeOut* fadeOut4 = FadeOut::create(ONE_SECOND*2);
	mai_Sprite->runAction(fadeOut1) ;
	ke_Sprite->runAction(fadeOut2) ; 
	ji_Sprite->runAction(fadeOut3) ;

	CallFunc* callFunc4 = CallFunc::create(CC_CALLBACK_0(SplashScene::gotoMenuScene, this));
	cheng_Sprite->runAction(Sequence::create(fadeOut4,callFunc4,NULL));
}

void SplashScene::gotoMenuScene()

{

	log("goto MenuScene");

	Director::getInstance()->replaceScene(MenuScene::createScene());
}