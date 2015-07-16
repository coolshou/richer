#ifndef __ITEM_FOG_H__
#define __ITEM_FOG_H__

#include "Item.h"


class Item_fog :	public Item
{
public:
	Item_fog();
	~Item_fog();
	bool init();
	void addItemSpriteFrameCache();
	 CREATE_FUNC(Item_fog);
	CC_SYNTHESIZE(Animate* ,normal_anmi,Normal_anmi);
private:
	SpriteFrameCache* itemSpriteFrameCache;
	char name[20];
	Vector<SpriteFrame*> item_anim_vector;
	void setItemAnimate();

};

#endif