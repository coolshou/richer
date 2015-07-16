#ifndef __ITEM__STRETCHER_H__
#define __ITEM__STRETCHER_H__

#include "Item.h"


class Item_stretcher :	public Item
{
public:
	Item_stretcher();
	~Item_stretcher();
	bool init();
	void addItemSpriteFrameCache();
	CREATE_FUNC(Item_stretcher);

	CC_SYNTHESIZE(Animate* ,stretcher_empty_anmi,Stretcher_empty_anmi);
	CC_SYNTHESIZE(Animate* ,stretcher_full_anmi,Stretcher_full_anmi);

	Vector<SpriteFrame*> item_stretcher_empty_anim_vector;
	Vector<SpriteFrame*> item_stretcher_full_anim_vector;
private:
	SpriteFrameCache* itemSpriteFrameCache;
	char name[20];

	void setItemAnimate();

};

#endif