#include "LotteryCard.h"

bool LotteryCard::init()
{
    if(!Sprite::init())
    {
        return false;
    }
    return true;
}


LotteryCard* LotteryCard::createCardSprite(int numbers,int width,int height,float CardSpriteX,float CardSpriteY)
{
    LotteryCard* lotterycard = new LotteryCard();
    if(lotterycard && lotterycard->init())
    {
        lotterycard->autorelease();
        lotterycard->cardInit(numbers, width, height, CardSpriteX, CardSpriteY);
 
        return lotterycard;
    }
 
    CC_SAFE_DELETE(lotterycard);
    return NULL;
}

void LotteryCard::cardInit(int numbers,int width,int height,float CardSpriteX,float CardSpriteY)
{
    //设置初始化值
    lotteryNumber = numbers;
 
    //加入游戏的背景颜色
    layerColorBG = LayerColor::create(Color4B(100,100,100,255),width-5,height-5);
    layerColorBG->setPosition(Point(CardSpriteX,CardSpriteY));
 
    if(lotteryNumber > 0)
    {
		ballMenuImage = MenuItemImage::create("images/lt_defalut_ball.png", "images/lt_blueball.png", this, menu_selector(LotteryCard::ballButtonCallback));
		ballMenuImage->setTag(lotteryNumber);
		ballMenuImage->setPosition(Point(layerColorBG->getContentSize().width/2,layerColorBG->getContentSize().height/2));

		// 添加文字说明并设置位置
		labelLotteryNumber = LabelTTF::create(String::createWithFormat("%i",lotteryNumber)->getCString(),"HiraKakuProN-W6",25);
		labelLotteryNumber->setColor(Color3B(200,200,200));
        labelLotteryNumber->setPosition(Point(layerColorBG->getContentSize().width/2,layerColorBG->getContentSize().height/2));

		ballMenuImage->addChild(labelLotteryNumber);	

		Menu* menu = Menu::create();
		menu->setPosition(CCPointZero);
		layerColorBG->addChild(menu);
		menu->addChild(ballMenuImage);
		this->setTag(lotteryNumber);
    }
 
    this->addChild(layerColorBG);
	
}

void LotteryCard::ballButtonCallback(CCObject* pSender)
{
	Util::playAudioEffect(LOTTERY_EFFECT,false);
	Node* node = dynamic_cast<Node*>(pSender);
	ballMenuImage->selected();
	if (m_callback && m_callbackListener)
	{
        (m_callbackListener->*m_callback)(node);
    }
}

void LotteryCard::setUnSelected()
{
	ballMenuImage->unselected();
}

void LotteryCard::setBallCallbackFunc(cocos2d::Object *target, SEL_CallFuncN callfun)
{
    m_callbackListener = target;
    m_callback = callfun;    
}

int LotteryCard::getLotteryNumber()
{
    return lotteryNumber;
}
 
void LotteryCard::setLotteryNumber(int num)
{
    lotteryNumber = num;
 
    if(lotteryNumber > 0)
    {
        labelLotteryNumber->setString(String::createWithFormat("%i",lotteryNumber)->getCString());
    }

}