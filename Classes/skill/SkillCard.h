#ifndef __SKILL_CARD_H__
#define __SKILL_CARD_H__
 
#include "cocos2d.h"
#include "Util.h"
#include "ConstUtil.h"
USING_NS_CC;

class SkillCard : public Sprite
{
public:
    static SkillCard* createCardSprite(String* skillName,String* skillGrade,String* strength,String* info,int width,int height,float x,float y,int tag,char* image);
    void cardInit(String* skillName,String* skillGrade,String* strength,String* info,int width,int height,float x,float y,int tag,char* image);
	virtual bool init();
    CREATE_FUNC(SkillCard);
    void setInfo(String* c);
	void setSkillGrade(int grade);
	void setStength(int strength);
	LayerColor* layerColorBG;

	LabelTTF* labelInfo;
	LabelTTF* labelName;
	LabelTTF* labelGrade;
	LabelTTF* labelStrength;
	 void setSkillButtonCallback(cocos2d::Object *target, SEL_CallFuncN callfun);
private:

   String* skillName;
   String* skillGrade;
   String* strength;
   String* info;
   MenuItemImage* menuImage;
   void buttonCallback(CCObject* pSender);
  
    
    CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);
   
	CCObject* m_callbackListener;
    SEL_CallFuncN m_callback;
};
 
#endif 