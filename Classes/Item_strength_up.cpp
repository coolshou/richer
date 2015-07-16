#include "Item_strength_up.h"


Item_strength_up::Item_strength_up()
{
}


Item_strength_up::~Item_strength_up()
{
	free(name);
	normal_anmi->release();
}

bool Item_strength_up::init()
{
	addItemSpriteFrameCache();
	SpriteFrame* spf;
	spf = itemSpriteFrameCache->getSpriteFrameByName("strength_up_01.png");

	Sprite::initWithSpriteFrame(spf);
	setItemAnimate();
	return true;
}

void Item_strength_up::addItemSpriteFrameCache()
{
	itemSpriteFrameCache = SpriteFrameCache::getInstance();
	itemSpriteFrameCache->addSpriteFramesWithFile("images/strength_up.plist","images/strength_up.png");

	memset(name, 0, 20);

	for (int i=1; i<=14; i++) 
	{
		sprintf(name, "strength_up_%02d.png",i);
		item_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}

}

void Item_strength_up::setItemAnimate()
{
	if(!AnimationCache::getInstance()->getAnimation("strength_up_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_anim_vector,0.1f),"strength_up_animation");
	}
	 normal_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("strength_up_animation"));
	 normal_anmi->retain();
}