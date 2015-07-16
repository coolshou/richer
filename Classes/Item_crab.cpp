#include "Item_crab.h"


Item_crab::Item_crab()
{
}


Item_crab::~Item_crab()
{
	free(name);
	normal_anmi->release();
}

bool Item_crab::init()
{
	addItemSpriteFrameCache();
	SpriteFrame* spf;
	spf = itemSpriteFrameCache->getSpriteFrameByName("crab_01.png");

	Sprite::initWithSpriteFrame(spf);
	setItemAnimate();
	return true;
}

void Item_crab::addItemSpriteFrameCache()
{
	itemSpriteFrameCache = SpriteFrameCache::getInstance();
	itemSpriteFrameCache->addSpriteFramesWithFile("images/crab.plist","images/crab.png");

	memset(name, 0, 20);

	for (int i=1; i<=4; i++) 
	{
		sprintf(name, "crab_%02d.png",i);
		item_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}

}

void Item_crab::setItemAnimate()
{
	if(!AnimationCache::getInstance()->getAnimation("normal_crab_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_anim_vector,0.5f),"normal_crab_animation");
	}
	 normal_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("normal_crab_animation"));
	 normal_anmi->retain();
}