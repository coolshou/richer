#include "Item_ball.h"


Item_ball::Item_ball()
{
}


Item_ball::~Item_ball()
{
	free(name);
	normal_anmi->release();
}

bool Item_ball::init()
{
	addItemSpriteFrameCache();
	SpriteFrame* spf;
	spf = itemSpriteFrameCache->getSpriteFrameByName("ball_01.png");

	Sprite::initWithSpriteFrame(spf);
	setItemAnimate();
	return true;
}

void Item_ball::addItemSpriteFrameCache()
{
	itemSpriteFrameCache = SpriteFrameCache::getInstance();
	itemSpriteFrameCache->addSpriteFramesWithFile("images/ball.plist","images/ball.png");

	memset(name, 0, 20);

	for (int i=1; i<=3; i++) 
	{
		sprintf(name, "ball_%02d.png",i);
		item_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}

}

void Item_ball::setItemAnimate()
{
	if(!AnimationCache::getInstance()->getAnimation("ball_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_anim_vector,0.4f),"ball_animation");
	}
	 normal_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("ball_animation"));
	 normal_anmi->retain();
}