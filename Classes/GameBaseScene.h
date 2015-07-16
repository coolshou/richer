#ifndef __GAME_BASE_SCENE_H__
#define __GAME_BASE_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ConstUtil.h"
#include "RicherPlayer.h"
#include "RouteNavigation.h"
#include "PopupLayer/PopupLayer.h"
#include "PopupLayer/CocosToast.h"
#include "Util.h"
#include "Item.h"
#include "Item_crab.h"
#include "Item_emergency.h"
#include "Item_stretcher.h"
#include "Item_fog.h"
#include "Item_ball.h"
#include "Item_strength_up.h"
#include "stock/LineChart.h"
#include "skill/SkillCard.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;

USING_NS_CC;
USING_NS_CC_EXT;

const int tableStartPosition_x = 650;
const int tableStartPosition_y = 450;
const int tableWidth = 50;
const int tableHeight = 40;
const int tiledWidth = 32;
const int tiledHeight = 32;
const int FONT_SIZE = 20;

const int Dialog_Size_Width = 400;
const int Dialog_Size_Height = 220;

const int Btn_OK_TAG = 1;
const int Btn_Cancel_TAG = 0;
const float stepSkillAnimaTime = 0.1;

const int goButtonTag = 700;
const int skillButtonTag = 701;
const int skillStormTag = 702;
const int skillStepTag = 703;
const int skillTransferTag = 704;
const int saveButtonTag = 705;
const int audioButtonTag = 706;
const int stepBaseTag = 800;
const int step1_tag = stepBaseTag+1;
const int step2_tag = stepBaseTag+2;
const int step3_tag = stepBaseTag+3;
const int step4_tag = stepBaseTag+4;
const int step5_tag = stepBaseTag+5;
const int step6_tag = stepBaseTag+6;


const int skillSpriteCardWidth = 150;
const int skillSpriteCardHeight = 100;

const int Quit_OK_TAG = 801;
const int Quit_Cancel_TAG = 802;

class GameBaseScene: public Layer
{
public:
	static int tiledColsCount;
	static int tiledRowsCount;
	
	static bool** canPassGrid;

	static Vector<Sprite*> pathMarkVector;

	static int blank_land_tiledID;
	static int strength_30_tiledID;
	static int strength_50_tiledID;
	static int strength_80_tiledID;

	static int randomEvent_tiledID;
	static int lottery_tiledID;
	static int stock_tiledID;

	static int player1_building_1_tiledID;
	static int player1_building_2_tiledID;
	static int player1_building_3_tiledID;

	static int player2_building_1_tiledID;
	static int player2_building_2_tiledID;
	static int player2_building_3_tiledID;

	MenuItemImage* goMenuItemButton ;
	MenuItemImage* skillMenuItemButton;
	MenuItemImage* saveMenuItemButton ;
	MenuItemImage* audioMenuItemButton;
	MenuItem* backItem;

	std::vector<Vec2> wayLayerPass_vector;

	RicherPlayer* player1;
	RicherPlayer* player2;
	RicherPlayer* player3;
	int map_level;
	char* saveJsonName;

    static Scene* createScene();
  	static TMXTiledMap* _map;
    virtual bool init();  
	void back(Object*);
	void quitButtonCallback(Node *pNode);
	//virtual void addMap();
	//virtual void initTiledGrid();
	void setWayPassToGrid();
	void onExit();

	void addPlayerAnimation();
	void goButtonCallback(CCObject* pSender);
    CREATE_FUNC(GameBaseScene);
	 
	static Vector<RicherPlayer*> players_vector;
	static void drawPathColor(std::vector<int> rowVector,std::vector<int> colVector);


	static TMXLayer* landLayer;
	static TMXLayer* wayLayer;

	void initLandLayerFromMap();

	//virtual void initPropTiledID(); 
    void setPlayer1InVisible(float dt);
	void setPlayer2InVisible(float dt);

	vector<float> stock_pointvec1;
	vector<float> stock_pointvec2;
	vector<float> stock_pointvec3;
	vector<float> stock_pointvec4;
	vector<float> stock_pointvec5;
	Vector<Stock*> stockVector;

	void skillClick(Node *pNode);

private:
	char money1[20];
	char money2[20];

	char strength1[20];
	char strength2[20];
	void drawTable(int playerNumber);
	void addPlayer();
	void addRightBanner();
	void addGoButton();
	void registerNotificationObserver();
	void receivedNotificationOMsg(Object* data);
	Map<int,__String*> randomAskEventMap;

	//SpriteFrameCache* diceFrameCache;
	 CC_SYNTHESIZE(Menu*, _menu, Menu);
	 CC_SYNTHESIZE(LabelTTF *, player1_money_label, Player1_money_label);
     CC_SYNTHESIZE(LabelTTF *, player2_money_label, Player2_money_label);

	 CC_SYNTHESIZE(LabelTTF *, player1_strength_label, Player1_strength_label);
	 CC_SYNTHESIZE(LabelTTF *, player2_strength_label, Player2_strength_label);
	 
	 void addPlayerInfo();
	// void addDice();
	 CC_SYNTHESIZE(Animate *, dice_animate, Dice_animate);
	 CC_SYNTHESIZE(Sprite *, diceSprite, DiceSprite);
	int randNumber ;
	void addPathMark();
	
	Vector<SpriteFrame*>  digiteRoundVector;
	Vector<Sprite*> refreshRoundVector;
	int gameRoundCount;
	void refreshRoundDisplay();
	void addDigiteRoundSprite();
	void initRandomAskEvent();
	void doRandomAskEvent(RicherPlayer* player);

	void  showBuyLandDialog(int landTag);
	void buyLandCallback(Node *pNode);

	PopupLayer* popDialog;
	void initPopDialog();

	float buy_land_x;
	float buy_land_y;


	void sendMSGPickOneToGO();
	void sendMSGPickOneToGO2(float dt);
	void sendMSGDealAroundLand(float dt);
	void sendMSGMoveOneStep();
	void sendMSGDealAroundLand2();
	void doSomeForParticle();
	Sprite* circleSprite;

	ActionInterval * scaleby1ForBuyLand;  
	ActionInterval * scaleby2ForBuyLand;  
	Sprite* foot1Sprite;
	Sprite* foot2Sprite;
	Sprite* starFish1Sprite;
	Sprite* starFish2Sprite;
	Sprite* heart1Sprite;
	Sprite* heart2Sprite;
	FadeOut* landFadeOut;
	FadeIn* landFadeIn;
	Vector<Sprite*> displayVector;

	RicherPlayer* getPlayerByTiled(float x,float y);
	void refreshMoneyLabel(RicherPlayer* player,int money);
	void refreshStrengthLabel(RicherPlayer* player,int strength);
	void payTolls(int payTag,float x,float y ,int playerTag);
	void playParticle(Point point ,char* plistName);
	void buyLand(int buyTag,float x,float y ,Sprite* landSprite,int landLevel,RicherPlayer* player ,char* particlelistName);
	int displayArea(float x,float y,RicherPlayer* player,int building_1_tiledID,int building_2_tiledID,int building_3_tiledID);

	void initItemSprite();
	Item_crab* item_crab;
	Item_ball* item_ball;
	Item_strength_up* item_strength_up;
	void registerBlockWaySchedule();
	void updateBlockWaySprites(float dt);
	void doBlockWayEvent(RicherPlayer* player);
	void endCarGo();
	void startCarGoAgain();
	Item_emergency* emerg;
	Item_stretcher* strentcher;
	Item_fog* fog;
	void endCarGoLast();
	void sendMSGForHandleProp(float dt);
	void doItemStrengthUp(int strengthUp,int playerTag);
	void lotteryButtonCallback(Node *pNode);
	int moveTag;
	void popPublishLottery(float dt);
	PopupLayer* popDialogLottery;
	void initPopPublishLottery();
	void showGoButton();
	void updateStockVec();
	void initStockVector(RicherPlayer* player);
	void doStockDeal(RicherPlayer* player,int moveTag);
	SkillCard* skillStorm;
	SkillCard* skillStep;
	SkillCard* skillTransfer;
	bool isSkillLayerShow;
	bool isStepLayerShow;
	void  showStepButton(bool show);
	void  showSkillSprites();
	MenuItemImage* step1Button;
	MenuItemImage* step2Button;
	MenuItemImage* step3Button;
	MenuItemImage* step4Button;
	MenuItemImage* step5Button;
	MenuItemImage* step6Button;
	char name[20];
	Vector<SpriteFrame*> rain_anim_vector;
	Sprite* rainSprite;
	Sprite* transferSprite;
	int transferLandTag;
	bool saveGame();
	bool reloadGame(int map_level);
	void playerBgMusic(float fDelta);
	vector<char*> bgMusicVector;
	void initAudioEffect();
	Vector<String*> player2EffectVec_1;//交过路费声音0-6
	Vector<String*> player2EffectVec_2;//抢夺别人地块7-10
	Vector<String*> player2EffectVec_3;//房屋被抢夺11-14
	Vector<String*> player2EffectVec_4;//摧毁别人房屋15-18
	Vector<String*> player2EffectVec_5;//房屋被摧毁19-22
	Vector<String*> player2EffectVec_6;//螃蟹伤人23-26

	Vector<String*> player2EffectVec_7;//看到别人住院27-28
	Vector<String*> player2EffectVec_8; // 收取过路费29 - 34
	Vector<String*> player2EffectVec_9;//升级房子35-36
	Vector<String*> player2EffectVec_10; // 不交过路费37 - 38
	Vector<String*> player2EffectVec_11; // 买地39 - 42
	Vector<String*> player2EffectVec_12;//捡到珍珠43-44
	Vector<String*> player2EffectVec_13;//对方被罚收税45-48


	Vector<String*> player1EffectVec_1;//交过路费声音0-6
	Vector<String*> player1EffectVec_2;//抢夺别人地块7-10
	Vector<String*> player1EffectVec_3;//房屋被抢夺11-14
	Vector<String*> player1EffectVec_4;//摧毁别人房屋15-18
	Vector<String*> player1EffectVec_5;//房屋被摧毁19-22
	Vector<String*> player1EffectVec_6;//螃蟹伤人23-26

	Vector<String*> player1EffectVec_7;//看到别人住院27-28
	Vector<String*> player1EffectVec_8; // 收取过路费29 - 34
	Vector<String*> player1EffectVec_9;//升级房子35-36
	Vector<String*> player1EffectVec_10; // 不交过路费37 - 38
	Vector<String*> player1EffectVec_11; // 买地39 - 42
	Vector<String*> player1EffectVec_12;//捡到珍珠43-44
	Vector<String*> player1EffectVec_13;//对方被罚收税45-48

	Vector<String*> nextPlayerEffectVec;
	void playNextEffectVec(float t);


};

#endif