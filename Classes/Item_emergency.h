#ifndef __ITEM__EMERGENCY_H__
#define __ITEM__EMERGENCY_H__

#include "Item.h"


class Item_emergency :	public Item
{
public:
	Item_emergency();
	~Item_emergency();
	bool init();
	void addItemSpriteFrameCache();
	 CREATE_FUNC(Item_emergency);
	CC_SYNTHESIZE(Animate* ,car_go_anmi2,Car_go_anmi);
	CC_SYNTHESIZE(Animate* ,car_stop_anmi,Car_stop_anmi);
//	CC_SYNTHESIZE(Animate* ,stretcher_empty_anmi,Stretcher_empty_anmi);
//	CC_SYNTHESIZE(Animate* ,stretcher_full_anmi,Stretcher_full_anmi);
	Vector<SpriteFrame*> item_cargo_anim_vector;
	Vector<SpriteFrame*> item_carstop_anim_vector;
//	Vector<SpriteFrame*> item_stretcher_empty_anim_vector;
//	Vector<SpriteFrame*> item_stretcher_full_anim_vector;
private:
	SpriteFrameCache* itemSpriteFrameCache;
	char name[20];

	void setItemAnimate();

};

#endif