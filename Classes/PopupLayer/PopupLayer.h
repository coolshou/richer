#ifndef __crossDT_PopupLayer__
#define __crossDT_PopupLayer__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "LotteryCard.h"

#include "RicherPlayer.h"
#include "lottery/EllipseBy.h"


USING_NS_CC;
using namespace cocos2d::extension;

const int Pop_FontSize = 20;
const int save_beach_tag = 1;
const int save_sea_tag = 2;
const int save_snow_tag = 3;

enum POP_TYPE
{
	NORMAL,
	LOTTERY,
	LOTTERY_PUBLISH,
	LOADGAME,
};

class PopupLayer :public Layer
{
public:
	PopupLayer();
	~PopupLayer();
	virtual bool init();
	CREATE_FUNC(PopupLayer);

	Vector<RicherPlayer*> players_vector;
	static PopupLayer * create(const char* backgroundImage);
	void setTitle(const char* title ,int fontsize=Pop_FontSize);
	void setContentText(const char* text ,int fontsize=Pop_FontSize ,int padding=50 ,int paddintTop=100);
	void setLotteryContext(Size size);
	void setPublishLotteryContext(Size size);
	void setPlayerVector(Vector<RicherPlayer*> _vector);
	void setCallbackFunc(Object* target, SEL_CallFuncN callfun);
	
	bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag=0);
	virtual void onEnter();
	virtual void onExit();
	POP_TYPE pop_type;
	void setPopType(POP_TYPE type);
	Vector<LotteryCard*> lotteryVector;
	void refreshBallBackGround(Node *pNode);
	int lottery_selected;
	std::vector<int> selected_number_vector;
	void setHasSelectedLotteryNumber(std::vector<int> _vector);

	void setLoadGameContext(Size size);
	MenuItemImage* beachLoadGameMenuItem;
	MenuItemImage* seaLoadGameMenuItem;
	MenuItemImage* snowLoadGameMenuItem;
	void loadGameButtonCallback(cocos2d::CCObject *pSender);
private:
	void buttonCallback(CCObject* pSender);

    // 文字内容两边的空白区
    int m_contentPadding;
    int m_contentPaddingTop;
    
    CCObject* m_callbackListener;
    SEL_CallFuncN m_callback;

    CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);
    CC_SYNTHESIZE_RETAIN(Sprite*, m__sfBackGround, SpriteBackGround);
    CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m__s9BackGround, Sprite9BackGround);
    CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltTitle, LabelTitle);
    CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltContentText, LabelContentText);

	CC_SYNTHESIZE(int, dataTag, DataTag);
	void addPlayersInfo(Size size);
	Sprite* lp;
	void realRunPublishAnmi(float dt);
	void runPublishAnmi();
	void dismissFromParent(float dt);
	Vector<LabelTTF*> playerLotteryVector;
	void addPlayersLottery();
	char name[20];
	Sprite* m_turnBg;
	LayerColor* awardLayer;
	void onTurnEnd();
	ParticleSystemQuad * m_pElliRtt_1;
	ParticleSystemQuad * m_pElliRtt_2;
	ParticleSystemQuad * m_pCircle_1;
	ParticleSystemQuad * m_pCircle_2;
	int lottNumber;
};


#endif