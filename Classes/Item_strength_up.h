#ifndef __ITEM_STRENGTH_UP_H__
#define __ITEM_STRENGTH_UP_H__

#include "Item.h"


class Item_strength_up :	public Item
{
public:
	Item_strength_up();
	~Item_strength_up();
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