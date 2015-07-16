#ifndef __STOCKCELLCARD_H__
#define __STOCKCELLCARD_H__
 
#include "cocos2d.h"
USING_NS_CC;

class StockCellCard : public Sprite
{
public:
    static StockCellCard* createCardSprite(String* _info,int width,int height,float CardSpriteX,float CardSpriteY,int colorTag);
    virtual bool init();
    CREATE_FUNC(StockCellCard);
    void setInfo(String* c);
	LayerColor* layerColorBG;
	LabelTTF* labelInfo;
private:

    String* info;
    void cardInit(String* _info,int width,int height,float CardSpriteX,float CardSpriteY,int colorTag);
    MenuItemImage* ballMenuImage;

    
    CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);

    
	 CCObject* m_callbackListener;
    SEL_CallFuncN m_callback;
};
 
#endif 