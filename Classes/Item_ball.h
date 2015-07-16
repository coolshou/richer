#ifndef __ITEM_BALL_H__
#define __ITEM_BALL_H__

#include "Item.h"


class Item_ball :	public Item
{
public:
	Item_ball();
	~Item_ball();
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