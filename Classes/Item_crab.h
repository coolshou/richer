#ifndef __ITEM_CRAB_H__
#define __ITEM_CRAB_H__

#include "Item.h"


class Item_crab :	public Item
{
public:
	Item_crab();
	~Item_crab();
	bool init();
	void addItemSpriteFrameCache();
	CC_SYNTHESIZE(Animate* ,normal_anmi,Normal_anmi);
private:
	SpriteFrameCache* itemSpriteFrameCache;
	char name[20];
	Vector<SpriteFrame*> item_anim_vector;
	void setItemAnimate();

};

#endif