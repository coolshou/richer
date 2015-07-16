#include "SkillCard.h"

bool SkillCard::init()
{
    if(!Sprite::init())
    {
        return false;
    }
    return true;
}


SkillCard* SkillCard::createCardSprite(String* skillName,String* skillGrade,String* strength,String* info,int width,int height,float x,float y,int tag,char* image)
{
    SkillCard* skillCard = new SkillCard();
    if(skillCard && skillCard->init())
    {
        skillCard->autorelease();
        skillCard->cardInit(skillName, skillGrade, strength, info, width, height, x, y,tag,image);
 
        return skillCard;
    }
 
    CC_SAFE_DELETE(skillCard);
    return NULL;
}

void SkillCard::cardInit(String* skillName,String* skillGrade,String* strength,String* info,int width,int height,float x,float y,int tag,char* image)
{
    skillName =skillName;
	info = info;
	skillGrade =skillGrade;
	strength =strength;

	layerColorBG = LayerColor::create(Color4B(100,120,90,255),width,height);

   
    layerColorBG->setPosition(Point(x,y));

	Sprite* skillImage = Sprite::create(image);
	skillImage->setPosition(Point(0,layerColorBG->getContentSize().height));
	layerColorBG->addChild(skillImage);


	labelName = LabelTTF::create(skillName->getCString(),"",15);
	labelName->setColor(Color3B(200,200,200));
	labelName->setPosition(Point(layerColorBG->getContentSize().width/2-labelName->getContentSize().width/2,layerColorBG->getContentSize().height-5));
	labelName->setAnchorPoint(ccp(0,1));
	layerColorBG->addChild(labelName);

 	labelGrade = LabelTTF::create(skillGrade->getCString(),"",15);
	labelGrade->setColor(Color3B(200,200,200));
    labelGrade->setPosition(Point(5,layerColorBG->getContentSize().height/2));
	labelGrade->setAnchorPoint(ccp(0,0));
	layerColorBG->addChild(labelGrade);



	MenuItemImage* check = MenuItemImage::create("images/check_normal.png", "images/check_pressed.png", this, menu_selector(SkillCard::buttonCallback));
	check->setPosition(Point(layerColorBG->getContentSize().width-check->getContentSize().width,layerColorBG->getContentSize().height/2));
	check->setTag(tag);
		Menu* menu = Menu::create();
		menu->setPosition(CCPointZero);
		layerColorBG->addChild(menu);

		menu->addChild(check);

	labelStrength = LabelTTF::create(strength->getCString(),"",15);
	labelStrength->setColor(Color3B(200,200,200));
    labelStrength->setPosition(Point(5,layerColorBG->getContentSize().height/2-20));
	labelStrength->setAnchorPoint(ccp(0,0));
	layerColorBG->addChild(labelStrength);

    if(info != NULL)
    {

		labelInfo = LabelTTF::create(info->getCString(),"",15);
		labelInfo->setColor(Color3B(200,200,200));
        labelInfo->setPosition(Point(5,layerColorBG->getContentSize().height/2-40));
		labelInfo->setAnchorPoint(ccp(0,0));
		layerColorBG->addChild(labelInfo);
    }
    this->addChild(layerColorBG);
	
}

void SkillCard::buttonCallback(CCObject* pSender)
{
	Node* node = dynamic_cast<Node*>(pSender);

	if (m_callback && m_callbackListener)
	{
        (m_callbackListener->*m_callback)(node);
    }
}
void SkillCard::setSkillButtonCallback(cocos2d::Object *target, SEL_CallFuncN callfun)
{
    m_callbackListener = target;
    m_callback = callfun;    
}

 
void SkillCard::setInfo(String* c)
{
   info = c;
   labelInfo->setString(c->getCString());

}

void SkillCard::setSkillGrade(int grade)
{
	// labelGrade->setString(c->getCString());
	labelGrade->setString(String::createWithFormat("%s: %d/5",LanguageString::getInstance()->getLanguageString(GRADE)->getCString(),grade)->getCString());
	
}
void SkillCard::setStength(int strength)
{
	// labelStrength->setString(c->getCString());
	labelStrength->setString(String::createWithFormat("%s: %d",LanguageString::getInstance()->getLanguageString(LOST_STRENGTH)->getCString(),strength)->getCString());
}