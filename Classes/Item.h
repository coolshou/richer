#ifndef __Item_H__
#define __Item_H__

#include "cocos2d.h"
#include "ConstUtil.h"


USING_NS_CC;

class Item : public Sprite
{
public:
	Item();
	~Item();

	ITEM_TYPE _type;
	static Item* create(ITEM_TYPE type);
	virtual bool init() = 0;
	virtual void addItemSpriteFrameCache() =0;
};

#endif
