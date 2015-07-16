#ifndef __LOTTERY_CARD_H__
#define __LOTTERY_CARD_H__
 
#include "cocos2d.h"
#include "Util.h"
USING_NS_CC;

class LotteryCard : public Sprite
{
public:
    //初始化的数值，宽度，高度，卡片X轴，卡片Y轴
    static LotteryCard* createCardSprite(int numbers,int width,int height,float CardSpriteX,float CardSpriteY);
    virtual bool init();
    CREATE_FUNC(LotteryCard);
 
    //获取数字
    int getLotteryNumber();
    //设置数字
    void setLotteryNumber(int num);
    void ballButtonCallback(CCObject* pSender);
	void setUnSelected();
	void setBallCallbackFunc(Object* target, SEL_CallFuncN callfun);
private:
    //显示在界面中的数字
    int lotteryNumber;
    void cardInit(int numbers,int width,int height,float CardSpriteX,float CardSpriteY);
    MenuItemImage* ballMenuImage;
    //定义显示数字的控件
    LabelTTF* labelLotteryNumber;
    CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);
    //显示背景
    LayerColor* layerColorBG;
	 CCObject* m_callbackListener;
    SEL_CallFuncN m_callback;
};
 
#endif 