#include "Item.h"
#include "Item_crab.h"
#include "Item_ball.h"
#include "Item_strength_up.h"
Item::Item()
{
	
}


Item::~Item()
{
}


Item* Item::create(ITEM_TYPE type)
{
	Item* item;


	if (type == ITEM_CRAB)
	{
		item = new Item_crab();
	}	

	if (type == ITEM_BALL)
	{
		item = new Item_ball();
	}	
	if (type == ITEM_STRENGTH_UP)
	{
		item = new Item_strength_up();
	}	

	item->_type = type;
	item->init();
	item->autorelease();
	return item;
}




