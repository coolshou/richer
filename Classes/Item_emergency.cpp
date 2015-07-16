#include "Item_emergency.h"


Item_emergency::Item_emergency()
{
}


Item_emergency::~Item_emergency()
{
	free(name);
	car_go_anmi2->release();
	car_stop_anmi->release();
//	stretcher_empty_anmi->release();
//	stretcher_full_anmi->release();
}

bool Item_emergency::init()
{
	memset(name, 0, 20);
	addItemSpriteFrameCache();
	SpriteFrame* spf;
	spf = itemSpriteFrameCache->getSpriteFrameByName("car_01.png");
	setItemAnimate();
	Sprite::initWithSpriteFrame(spf);
	
	return true;
}

void Item_emergency::addItemSpriteFrameCache()
{
	itemSpriteFrameCache = SpriteFrameCache::getInstance();
	itemSpriteFrameCache->addSpriteFramesWithFile("images/car.plist","images/car.png");
//	itemSpriteFrameCache->addSpriteFramesWithFile("images/stretcher_empty.plist","images/stretcher_empty.png");
//	itemSpriteFrameCache->addSpriteFramesWithFile("images/stretcher.plist","images/stretcher.png");

	memset(name, 0, 20);
	for (int i=1; i<=2; i++) 
	{
		sprintf(name, "car_%02d.png",i);
		item_cargo_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}


	for (int i=3; i<=4; i++) 
	{
		sprintf(name, "car_%02d.png",i);
		item_carstop_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}
/*
//	memset(name, 0, 20);
	for (int i=1; i<=8; i++) 
	{
		sprintf(name, "stretcher%02d_empty.png",i);
		item_stretcher_empty_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}

//	memset(name, 0, 20);
	for (int i=1; i<=8; i++) 
	{
		sprintf(name, "stretcher%02d.png",i);
		item_stretcher_full_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}
*/
}

void Item_emergency::setItemAnimate()
{
	
	if(!AnimationCache::getInstance()->getAnimation("car_go_animation2"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_cargo_anim_vector,0.1f),"car_go_animation2");
	}
	 car_go_anmi2 = Animate::create(AnimationCache::getInstance()->getAnimation("car_go_animation2"));
	 car_go_anmi2->retain();


	if(!AnimationCache::getInstance()->getAnimation("car_stop_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_carstop_anim_vector,0.5f),"car_stop_animation");
	}
	 car_stop_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("car_stop_animation"));
	 car_stop_anmi->retain();
/*
	if(!AnimationCache::getInstance()->getAnimation("stretcher_empty_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_stretcher_empty_anim_vector,0.5f),"stretcher_empty_animation");
	}
	 stretcher_empty_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("stretcher_empty_animation"));
	 stretcher_empty_anmi->retain();


	if(!AnimationCache::getInstance()->getAnimation("stretcher_full_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_stretcher_full_anim_vector,0.5f),"stretcher_full_animation");
	}
	 stretcher_full_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("stretcher_full_animation"));
	 stretcher_full_anmi->retain();
*/
}