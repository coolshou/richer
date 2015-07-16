#include "Item_fog.h"


Item_fog::Item_fog()
{
}


Item_fog::~Item_fog()
{
	free(name);
	normal_anmi->release();
}

bool Item_fog::init()
{
	addItemSpriteFrameCache();
	SpriteFrame* spf;
	spf = itemSpriteFrameCache->getSpriteFrameByName("fog_01.png");

	Sprite::initWithSpriteFrame(spf);
	setItemAnimate();
	return true;
}

void Item_fog::addItemSpriteFrameCache()
{
	itemSpriteFrameCache = SpriteFrameCache::getInstance();
	itemSpriteFrameCache->addSpriteFramesWithFile("images/fog.plist","images/fog.png");

	memset(name, 0, 20);

	for (int i=1; i<=7; i++) 
	{
		sprintf(name, "fog_%02d.png",i);
		item_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}

}

void Item_fog::setItemAnimate()
{
	if(!AnimationCache::getInstance()->getAnimation("fog_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_anim_vector,0.2f),"fog_animation");
	}
	 normal_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("fog_animation"));
	 normal_anmi->retain();
}