#include "GameBaseScene.h"
#include "SimpleAudioEngine.h"

	 int GameBaseScene::tiledColsCount;
	 int GameBaseScene::tiledRowsCount;
	 bool** GameBaseScene::canPassGrid;
	 Vector<RicherPlayer*>  GameBaseScene::players_vector;
	 Vector<Sprite*> GameBaseScene::pathMarkVector;
	 TMXLayer* GameBaseScene::landLayer;
	 TMXLayer* GameBaseScene::wayLayer;
	 TMXTiledMap* GameBaseScene::_map;

     int  GameBaseScene::blank_land_tiledID;
	 int  GameBaseScene::strength_30_tiledID;
	 int  GameBaseScene::strength_50_tiledID;
	 int  GameBaseScene::strength_80_tiledID;

	 int  GameBaseScene::randomEvent_tiledID;
	 int  GameBaseScene::lottery_tiledID;
	 int  GameBaseScene::stock_tiledID;

	int GameBaseScene::player1_building_1_tiledID;
	int GameBaseScene::player1_building_2_tiledID;
	int GameBaseScene::player1_building_3_tiledID;

	int GameBaseScene::player2_building_1_tiledID;
	int GameBaseScene::player2_building_2_tiledID;
	int GameBaseScene::player2_building_3_tiledID;



Scene* GameBaseScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameBaseScene::create();

	scene->addChild(layer);

	return scene;

}


bool GameBaseScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	//addMap();
	//initTiledGrid();
	setWayPassToGrid();
	addRightBanner();
	drawTable(2);
	addPathMark();
	addPlayer();
	addGoButton();
	registerNotificationObserver();
	//addDice();
	addDigiteRoundSprite();
	refreshRoundDisplay();
	initLandLayerFromMap();
	initItemSprite();
	registerBlockWaySchedule();
	//initPropTiledID();
	initPopDialog();
	doSomeForParticle();
	initRandomAskEvent();
	initPopPublishLottery();
	memset(name, 0, 20);

	//Util::playRicherMusic(BG01_MP3,false);

	
	initAudioEffect();


	

	return true;
}

void GameBaseScene::initAudioEffect()
{
	bgMusicVector.push_back(BG01_MP3);
	bgMusicVector.push_back(BG02_MP3);
	bgMusicVector.push_back(BG03_MP3);

	for (int i = 0; i<bgMusicVector.size(); i++)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bgMusicVector.at(i));
	}
	this->schedule(schedule_selector(GameBaseScene::playerBgMusic), 5.0f);

	//交过路费声音0-6
	player2EffectVec_1.pushBack(String::create(P2_SPEAKING01));
	player2EffectVec_1.pushBack(String::create(P2_QISIWOLE));
	player2EffectVec_1.pushBack(String::create(P2_XINHAOKONGA));
	player2EffectVec_1.pushBack(String::create(P2_BUHUIBA));
	player2EffectVec_1.pushBack(String::create(P2_PAYHIGH));
	player2EffectVec_1.pushBack(String::create(P2_QIANGQIANA));
	player2EffectVec_1.pushBack(String::create(P2_HEBAOCHUXIE));

	//抢夺别人地块7-10
	player2EffectVec_2.pushBack(String::create(P2_BIEGUAIWO));
	player2EffectVec_2.pushBack(String::create(P2_SPEAKING02));
	player2EffectVec_2.pushBack(String::create(P2_TIGER));
	player2EffectVec_2.pushBack(String::create(P2_NIDEJIUSHODE));
	//房屋被抢夺11-14
	player2EffectVec_3.pushBack(String::create(P2_ZHENMIANMU));
	player2EffectVec_3.pushBack(String::create(P2_WODEDIQI));
	player2EffectVec_3.pushBack(String::create(P2_HAOQIFU));
	player2EffectVec_3.pushBack(String::create(P2_WANGFA));
	//摧毁别人房屋15-18
	player2EffectVec_4.pushBack(String::create(P2_NIGAIWOCHAI));
	player2EffectVec_4.pushBack(String::create(P2_KANWODE));
	player2EffectVec_4.pushBack(String::create(P2_HAIRENLE));
	player2EffectVec_4.pushBack(String::create(P2_BAOCHOU));
	//房屋被摧毁19-22
	player2EffectVec_5.pushBack(String::create(P2_WODEYANGFANG));
	player2EffectVec_5.pushBack(String::create(P2_QIFURENJIA));
	player2EffectVec_5.pushBack(String::create(P2_SHAQIANDAO));
	player2EffectVec_5.pushBack(String::create(P2_LIANXIANGXIYU));
	player2EffectVec_5.pushBack(String::create(P2_HAOJIUGAIHAO));
	//螃蟹伤人23-26
	player2EffectVec_6.pushBack(String::create(P2_YUNQICHA));
	player2EffectVec_6.pushBack(String::create(P2_HAIRENJING));
	player2EffectVec_6.pushBack(String::create(P2_XIAOHUANG));
	player2EffectVec_6.pushBack(String::create(P2_YISHENG));
	//看到别人住院27-28
	player2EffectVec_7.pushBack(String::create(P2_DUOXIUXI));
	player2EffectVec_7.pushBack(String::create(P2_XIUXIJITIAN));
	//收取过路费29-34
	player2EffectVec_8.pushBack(String::create(P2_RENBUWEIJI));
	player2EffectVec_8.pushBack(String::create(P2_XIAOQI));
	player2EffectVec_8.pushBack(String::create(P2_RONGXING));
	player2EffectVec_8.pushBack(String::create(P2_MANYI));
	player2EffectVec_8.pushBack(String::create(P2_XIAOFUPO));
	player2EffectVec_8.pushBack(String::create(P2_DUOGEI));
	//升级房子35-36
	player2EffectVec_9.pushBack(String::create(P2_HIGHER));
	player2EffectVec_9.pushBack(String::create(P2_WANZHANGGAOLOU));
	//不交过路费37-38
	player2EffectVec_10.pushBack(String::create(P2_NOTPAY));
	player2EffectVec_10.pushBack(String::create(P2_YIMAOBUGEI));
	//买地39-42
	player2EffectVec_11.pushBack(String::create(P2_BUYIT));
	player2EffectVec_11.pushBack(String::create(P2_HAODEKAISHI));
	player2EffectVec_11.pushBack(String::create(P2_RANGNIZHU));
	player2EffectVec_11.pushBack(String::create(P2_MAIWOBA));
	//捡到珍珠43-44
	player2EffectVec_12.pushBack(String::create(P2_DEYIDEYITIAN));
	player2EffectVec_12.pushBack(String::create(P2_HENGCAI));
	//对方被罚收税45-48
	player2EffectVec_13.pushBack(String::create(P2_TOUSHUI));
	player2EffectVec_13.pushBack(String::create(P2_FALVZHICAI));
	player2EffectVec_13.pushBack(String::create(P2_GUOKU));
	player2EffectVec_13.pushBack(String::create(P2_NASHUI));



	//交过路费声音
	player1EffectVec_1.pushBack(String::create(P1_Speaking_00435));
	player1EffectVec_1.pushBack(String::create(P1_Speaking_00461));
	player1EffectVec_1.pushBack(String::create(P1_Speaking_00475));
	player1EffectVec_1.pushBack(String::create(P1_Speaking_01060));
	player1EffectVec_1.pushBack(String::create(P1_Speaking_001062));
	//抢夺别人地块
	player1EffectVec_2.pushBack(String::create(P1_Speaking_00429));
	//房屋被抢夺
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00430));
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00464));
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00469));
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00470));
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00476));
	//摧毁别人房屋
	player1EffectVec_4.pushBack(String::create(P1_Speaking_00433));
	player1EffectVec_4.pushBack(String::create(P1_Speaking_00437));

	//房屋被摧毁
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00462));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00463));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00466));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00468));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00474));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_001061));
	//螃蟹伤人
	
	player1EffectVec_6.pushBack(String::create(P1_Speaking_00449));
	player1EffectVec_6.pushBack(String::create(P1_Speaking_01054));
	player1EffectVec_6.pushBack(String::create(P1_Speaking_01055));
	player1EffectVec_6.pushBack(String::create(P1_Speaking_001071));
	//看到别人住院
	player1EffectVec_7.pushBack(String::create(P1_Speaking_001073));
	//收取过路费
	player1EffectVec_8.pushBack(String::create(P1_Speaking_00453));
	player1EffectVec_8.pushBack(String::create(P1_Speaking_01059));
	player1EffectVec_8.pushBack(String::create(P1_Speaking_01057));
	//升级房子
	player1EffectVec_9.pushBack(String::create(P1_Speaking_01051));
	player1EffectVec_9.pushBack(String::create(P1_Speaking_001066));
	//不交过路费
	player1EffectVec_10.pushBack(String::create(P1_Speaking_00446));
	player1EffectVec_10.pushBack(String::create(P1_Speaking_00477));
	//买地
	player1EffectVec_11.pushBack(String::create(P1_Speaking_00458));
	player1EffectVec_11.pushBack(String::create(P1_Speaking_001067));
	player1EffectVec_11.pushBack(String::create(P1_Speaking_01051));

	//捡到珍珠
	player1EffectVec_12.pushBack(String::create(P1_Speaking_01052));
	player1EffectVec_12.pushBack(String::create(P1_Speaking_001063));
	//对方被罚收税
	player1EffectVec_13.pushBack(String::create(P1_Speaking_00452));



}

void GameBaseScene::back(Object*)
{
	PopupLayer* popDialog = PopupLayer::create(DIALOG_BG);
	popDialog->setContentSize(CCSizeMake(400, 200));
	popDialog->setTitle(LanguageString::getInstance()->getLanguageString(DIALOG_TITLE)->getCString());
	popDialog->setContentText(LanguageString::getInstance()->getLanguageString(DIALOG_CONTENT)->getCString(), 20, 60, 250);
	popDialog->setCallbackFunc(this, callfuncN_selector(GameBaseScene::quitButtonCallback));
	popDialog->addButton(BUTTON_BG1, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(OK)->getCString(), Quit_OK_TAG);
	popDialog->addButton(BUTTON_BG2, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(CANCEL)->getCString(), Quit_Cancel_TAG);
	this->addChild(popDialog);
	
}

void GameBaseScene::quitButtonCallback(Node *pNode)
{
	Util::playAudioEffect(BUTTON_CLICK, false);
	if (pNode->getTag() == Quit_OK_TAG)
	{
		Director::getInstance()->end();
	}
	else
	{
		pNode->getParent()->getParent()->removeFromParent();
	}

}

void GameBaseScene::playerBgMusic(float fDelta)
{
	if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{		
		Util::playRicherMusic(bgMusicVector.at(rand()%bgMusicVector.size()),false);
	}

}

void GameBaseScene::initPopPublishLottery()
{
	popDialogLottery = PopupLayer::create(DIALOG_BG);	
	popDialogLottery->setContentSize(CCSizeMake(Dialog_Size_Width, Dialog_Size_Height+180)); 
	popDialogLottery->setTitle(LanguageString::getInstance()->getLanguageString(PUBLISH_LOTTERY)->getCString());
	popDialogLottery->setContentText("", 20, 60, 250);
	popDialogLottery->setPopType(LOTTERY_PUBLISH);
	popDialogLottery->setPlayerVector(players_vector);
	popDialogLottery->setTag(100);
	this->addChild(popDialogLottery);	
	popDialogLottery->setVisible(false);
	
}


void GameBaseScene::initItemSprite()
{
	item_crab = (Item_crab*)Item::create(ITEM_CRAB);
	addChild(item_crab);
	item_crab->runAction(RepeatForever::create(item_crab->getNormal_anmi()));
	item_crab->setVisible(false);

    item_ball = (Item_ball*)Item::create(ITEM_BALL);
	addChild(item_ball);
	item_ball->runAction(RepeatForever::create(item_ball->getNormal_anmi()));
	item_ball->setVisible(false);


	item_strength_up = (Item_strength_up*)Item::create(ITEM_STRENGTH_UP);
	addChild(item_strength_up);
	item_strength_up->setVisible(false);

	item_strength_up->setAnchorPoint(ccp(0,0.5));

	emerg = Item_emergency::create();
    addChild(emerg);
	emerg->setVisible(false);

	fog = Item_fog::create();
	addChild(fog);
	fog->setVisible(false);

	strentcher = Item_stretcher::create();
	addChild(strentcher);
	strentcher->setVisible(false);
	strentcher->setAnchorPoint(ccp(0,0.9));
}

void GameBaseScene::registerBlockWaySchedule()
{
	schedule(schedule_selector(GameBaseScene::updateBlockWaySprites),10.0f);
}

void GameBaseScene::updateBlockWaySprites(float dt)
{
	int _rand1 = rand()%(wayLayerPass_vector.size()); 
	Vec2 position = wayLayerPass_vector.at(_rand1);
	position.x -= 5;
	position.y +=tiledHeight; 
	item_crab->setVisible(true);
	item_crab->setPosition(position);
	item_crab->setAnchorPoint(ccp(0,0.6));


	int _rand2 = rand()%(wayLayerPass_vector.size()); 
	Vec2 position2 = wayLayerPass_vector.at(_rand2);
	//position2.y +=tiledHeight; 
	item_ball->setVisible(true);
	item_ball->setPosition(position2);
	item_ball->setAnchorPoint(ccp(0,0));

}

void GameBaseScene::playNextEffectVec(float t)
{
	Util::playAudioEffectRandom(nextPlayerEffectVec, false);
}

void GameBaseScene::doBlockWayEvent(RicherPlayer* player)
{
	if(player->getBoundingBox().containsPoint(item_crab->getPosition()+ccp(item_crab->getContentSize().width/2,-item_crab->getContentSize().height/2)))
	{
		Util::playAudioEffect(M120,false);
		if (player->getTag() == PLAYER_2_TAG)
		{
			Util::playAudioEffectRandom(player2EffectVec_6,false);
			nextPlayerEffectVec = player1EffectVec_7;
			scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
			//Util::playAudioEffectRandom(player1EffectVec_7, false);
		}
		else if (player->getTag() == PLAYER_1_TAG)
		{
			Util::playAudioEffectRandom(player1EffectVec_6, false);
			nextPlayerEffectVec = player2EffectVec_7;
			scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
			//Util::playAudioEffectRandom(player2EffectVec_7, false);
		}
		item_crab->setPosition(ccp(-200, -200));
	
		player->restTimes =  rand()%(5) + 1;
		log("doBlockWayEvent intersetcRect");
		emerg->setVisible(true);
		int distance = tableStartPosition_x-player->getPosition().x;
		emerg->setPosition(player->getPosition()+ccp(distance,0));

		fog->setVisible(true);
		fog->setPosition(player->getPosition());
		Repeat* repeate0 = Repeat::create(fog->getNormal_anmi(),2);
		fog->runAction(repeate0);

		MoveBy* moveBy = MoveBy::create(1.0f,ccp(-distance,0));
		MoveBy* moveBy2 = MoveBy::create(0.5f,ccp(-60,0));
		Repeat* repeate = Repeat::create(emerg->getCar_go_anmi(),5);
		Repeat* repeate2 = Repeat::create(emerg->getCar_stop_anmi(),1);

		Sequence* spawnAction = Sequence::create(Spawn::create(moveBy,repeate,NULL),Spawn::create(moveBy2,repeate2,NULL),CallFunc::create(CC_CALLBACK_0(GameBaseScene::endCarGo, this)),NULL);
		spawnAction->retain();
		emerg->runAction(spawnAction);

		if(player->getTag() == PLAYER_1_TAG)
		{
			scheduleOnce(schedule_selector(GameBaseScene::setPlayer1InVisible),2.5f);	
		}else if(player->getTag() == PLAYER_2_TAG)
		{
			scheduleOnce(schedule_selector(GameBaseScene::setPlayer2InVisible),2.5f);	
		}
		CocosToast::createToast(this,String::createWithFormat("%s %d %s",LanguageString::getInstance()->getLanguageString(PLAYER_HURT)->getCString(),player->restTimes,LanguageString::getInstance()->getLanguageString(RICH_DAY)->getCString())->getCString(), TOAST_SHOW_TIME,player->getPosition());
	}else if(player->getBoundingBox().intersectsRect(item_ball->getBoundingBox()))
	{
		if (player->getTag() == PLAYER_2_TAG)
		{
			Util::playAudioEffectRandom(player2EffectVec_12, false);
		}
		else if (player->getTag() == PLAYER_1_TAG)
		{
			Util::playAudioEffectRandom(player1EffectVec_12, false);
		}
		item_ball->setPosition(ccp(-200,-200));
		int money =  10000;
		refreshMoneyLabel(player,money);
		CocosToast::createToast(this,String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(PICK_BALL)->getCString(),money)->getCString(),TOAST_SHOW_TIME,player->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGDealAroundLand2);
	}

	else
	{
		NotificationCenter::getInstance()->postNotification(MSG_HANDLE_PROP_EVENT,String::createWithFormat("%d",MSG_HANDLE_PROP_EVENT_TAG));
	}
}


void GameBaseScene::setPlayer1InVisible(float dt)
{
	player1->setVisible(false);
	fog->setVisible(false);
}

void GameBaseScene::setPlayer2InVisible(float dt)
{
	player2->setVisible(false);
	fog->setVisible(false);
}

void GameBaseScene::endCarGo()
{
	strentcher->setVisible(true);
	strentcher->setPosition(emerg->getPosition());
	MoveBy* moveBy = MoveBy::create(0.5f,ccp(60,0));
	ScaleBy* scaleBy = ScaleBy::create(0.5f,0.8);
	Repeat* repeate = Repeat::create(strentcher->getStretcher_empty_anmi(),1);
	ScaleBy* scaleBy2 = ScaleBy::create(0.5f,1.25);
	MoveBy* moveBy2 = MoveBy::create(0.5f,ccp(-60,0));
	Repeat* repeate2 = Repeat::create(strentcher->getStretcher_full_anmi(),1);
	Sequence* spawnAction = Sequence::create(Spawn::create(moveBy,scaleBy,repeate,NULL),Spawn::create(moveBy2,scaleBy2,repeate2,NULL),CallFunc::create(CC_CALLBACK_0(GameBaseScene::startCarGoAgain, this)),NULL);
	spawnAction->retain();
	strentcher->runAction(spawnAction);
}

void GameBaseScene::startCarGoAgain()

{
	strentcher->setVisible(false);
	int distance = emerg->getPositionX();
	MoveBy* moveBy = MoveBy::create(1.0f,ccp(-distance,0));
	Repeat* repeate = Repeat::create(emerg->getCar_go_anmi(),5);
	Sequence* spawnAction = Sequence::create(Spawn::create(moveBy,repeate,NULL),CallFunc::create(CC_CALLBACK_0(GameBaseScene::endCarGoLast, this)),NULL);
	spawnAction->retain();
	emerg->runAction(spawnAction);
}


void GameBaseScene::endCarGoLast()

{
	emerg->setVisible(false);
	NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));
}

void GameBaseScene::initRandomAskEvent()
{
	randomAskEventMap.insert(TAX_REBATES_TAG,LanguageString::getInstance()->getLanguageString(TAX_REBATES));
	randomAskEventMap.insert(PAY_TAXES_TAG,LanguageString::getInstance()->getLanguageString(PAY_TAXES));
	randomAskEventMap.insert(LOSS_STRENGTH_TAG,LanguageString::getInstance()->getLanguageString(LOSS_STRENGTH));
	randomAskEventMap.insert(PHYSICAL_RECOVERY_TAG,LanguageString::getInstance()->getLanguageString(PHYSICAL_RECOVERY));
	randomAskEventMap.insert(INVESTMENT_DIVIDENDS_TAG,LanguageString::getInstance()->getLanguageString(INVESTMENT_DIVIDENDS));
	randomAskEventMap.insert(INVESTMENT_LOSS_TAG,LanguageString::getInstance()->getLanguageString(INVESTMENT_LOSS));

	randomAskEventMap.insert(STORM_UP_TAG,LanguageString::getInstance()->getLanguageString(STORM_SKILL_UP));
	randomAskEventMap.insert(STEP_UP_TAG,LanguageString::getInstance()->getLanguageString(STEP_SKILL_UP));
	randomAskEventMap.insert(TRANSFER_UP_TAG,LanguageString::getInstance()->getLanguageString(TRANSFER_SKILL_UP));

}


void GameBaseScene::doSomeForParticle()
{
	landFadeOut = FadeOut::create(0.1);
	landFadeIn = FadeIn::create(0.1);
	landFadeOut->retain();
	landFadeIn->retain();	

	scaleby1ForBuyLand = ScaleBy::create(0.1, 1.5);  
	scaleby2ForBuyLand = ScaleBy::create(0.5, 0.7);  
	scaleby1ForBuyLand->retain();
	scaleby2ForBuyLand->retain();		
	foot1Sprite = Sprite::create(PLAYER1_1_PARTICLE_PNG);
	addChild(foot1Sprite);
	foot1Sprite->setAnchorPoint(ccp(0,0));

	foot2Sprite = Sprite::create(PLAYER2_1_PARTICLE_PNG);
	addChild(foot2Sprite);
	foot2Sprite->setAnchorPoint(ccp(0,0));

	starFish1Sprite = Sprite::create(PLAYER1_2_PARTICLE_PNG);
	addChild(starFish1Sprite);
	starFish1Sprite->setAnchorPoint(ccp(0,0));

	starFish2Sprite = Sprite::create(PLAYER2_2_PARTICLE_PNG);
	addChild(starFish2Sprite);
	starFish2Sprite->setAnchorPoint(ccp(0,0));

	heart1Sprite = Sprite::create(PLAYER1_3_PARTICLE_PNG);
	addChild(heart1Sprite);
	heart1Sprite->setAnchorPoint(ccp(0,0));

	heart2Sprite = Sprite::create(PLAYER2_3_PARTICLE_PNG);
	addChild(heart2Sprite);
	heart2Sprite->setAnchorPoint(ccp(0,0));


}


void GameBaseScene::initPopDialog()
{
	popDialog = PopupLayer::create(DIALOG_BG);
	
    popDialog->setContentSize(CCSizeMake(Dialog_Size_Width, Dialog_Size_Height)); 
    popDialog->setTitle(LanguageString::getInstance()->getLanguageString(DIALOG_TITLE)->getCString());
	popDialog->setContentText("", 20, 60, 250);
    popDialog->setCallbackFunc(this, callfuncN_selector(GameBaseScene::buyLandCallback));

    popDialog->addButton(BUTTON_BG1, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(OK)->getCString(), Btn_OK_TAG);
    popDialog->addButton(BUTTON_BG2, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(CANCEL)->getCString(), Btn_Cancel_TAG);
    this->addChild(popDialog);
	popDialog->setVisible(false);
}

void GameBaseScene::initLandLayerFromMap()
{
	landLayer = _map->layerNamed("land");
}

void GameBaseScene::addDigiteRoundSprite()
{
	gameRoundCount=0;
	auto frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("map/digital_round.plist");

	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_0));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_1));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_2));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_3));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_4));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_5));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_6));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_7));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_8));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_9));

}

void GameBaseScene::refreshRoundDisplay()
{

	for(auto it = refreshRoundVector.begin();it != refreshRoundVector.end();it++)
	{
		((Sprite*) *it)->setVisible(false);
	}

	refreshRoundVector.clear();
	int count = gameRoundCount;
	Sprite* st;
	/*
	if(gameRoundCount !=0 && gameRoundCount%1 == 0)
	{
		popPublishLottery();
	}
	*/
	if(count ==0 )
	{
		st = Sprite::createWithSpriteFrame(digiteRoundVector.at(0));
		addChild(st);
		refreshRoundVector.pushBack(st);
	}
	while(count!=0)
	{
		st = Sprite::createWithSpriteFrame(digiteRoundVector.at(count%10));
		addChild(st);
		refreshRoundVector.pushBack(st);
		count = count/10;

	}
	refreshRoundVector.reverse();

	for(int i = 0;i< refreshRoundVector.size();i++)
	{
		Sprite * sp = refreshRoundVector.at(i);
		sp->setPosition(ccp((tableStartPosition_x+50)+(i*25),50));
		sp->setVisible(true);
	}


	updateStockVec();

}

void GameBaseScene::updateStockVec()
{
	float valule1 = rand()%800+10;
	float valule2 = rand()%800+10;
	float valule3 = rand()%800+10;
	float valule4 = rand()%800+10;
	float valule5 = rand()%800+10;

	if(stock_pointvec1.size()>13)
	{
		for(int i=0;i<13;i++)
		{
			stock_pointvec1.at(i)=stock_pointvec1.at(i+1);
			stock_pointvec2.at(i)=stock_pointvec2.at(i+1);
			stock_pointvec3.at(i)=stock_pointvec3.at(i+1);
			stock_pointvec4.at(i)=stock_pointvec4.at(i+1);
			stock_pointvec5.at(i)=stock_pointvec5.at(i+1);
			
		}
		stock_pointvec1.at(13) =valule1;
		stock_pointvec2.at(13) =valule2;
		stock_pointvec3.at(13) =valule3;
		stock_pointvec4.at(13) =valule4;
		stock_pointvec5.at(13) =valule5;
	}else
	{
		stock_pointvec1.push_back(valule1);
		stock_pointvec2.push_back(valule2);
		stock_pointvec3.push_back(valule3);
		stock_pointvec4.push_back(valule4);
		stock_pointvec5.push_back(valule5);
	}
}

void GameBaseScene::popPublishLottery(float dt)
{
	popDialogLottery->setVisible(true);	
	popDialogLottery->addPlayersLottery();
	popDialogLottery->runPublishAnmi();
}

void GameBaseScene::addPathMark()
{
	
	Sprite* mark1 = Sprite::create(PATH_MARK_1);
	Sprite* mark2 = Sprite::create(PATH_MARK_2);
	Sprite* mark3 = Sprite::create(PATH_MARK_3);
	Sprite* mark4 = Sprite::create(PATH_MARK_4);
	Sprite* mark5 = Sprite::create(PATH_MARK_5);
	Sprite* mark6 = Sprite::create(PATH_MARK_6);


	mark1->setAnchorPoint(ccp(0,0));
	mark2->setAnchorPoint(ccp(0,0));
	mark3->setAnchorPoint(ccp(0,0));
	mark4->setAnchorPoint(ccp(0,0));
	mark5->setAnchorPoint(ccp(0,0));
	mark6->setAnchorPoint(ccp(0,0));

	mark1->setVisible(false);
	mark2->setVisible(false);
	mark3->setVisible(false);
	mark4->setVisible(false);
	mark5->setVisible(false);
	mark6->setVisible(false);


	addChild(mark1);
	addChild(mark2);
	addChild(mark3);
	addChild(mark4);
	addChild(mark5);
	addChild(mark6);

	pathMarkVector.pushBack(mark1);
	pathMarkVector.pushBack(mark2);
	pathMarkVector.pushBack(mark3);
	pathMarkVector.pushBack(mark4);
	pathMarkVector.pushBack(mark5);
	pathMarkVector.pushBack(mark6);
}

void GameBaseScene::drawPathColor(std::vector<int> rowVector,std::vector<int> colVector)
{
	int stepsCount = rowVector.size()-1;

	for(int i=1;i<rowVector.size();i++)
	{
		pathMarkVector.at(i-1)->setPosition(ccp(colVector[i]*32,rowVector[i]*32));
		pathMarkVector.at(i-1)->setVisible(true);
	}
}
/*
void GameBaseScene::addDice()
{
	diceFrameCache= SpriteFrameCache::getInstance();
	diceFrameCache->addSpriteFramesWithFile("map/dice.plist","map/dice.png");
	Vector<SpriteFrame*> diceVector ;

	char name[20];
	memset(name, 0, 20);
	for (int i=1; i<=6; i++) 
	{
		sprintf(name, "dice_%02d.png",i);
		diceVector.pushBack(diceFrameCache->getSpriteFrameByName(name));
	}

	if(!AnimationCache::getInstance()->getAnimation("dice_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(diceVector,0.1),"dice_animation");
	}
	dice_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dice_animation"));
	dice_animate->retain();
		
	diceSprite =Sprite::createWithSpriteFrame(diceFrameCache->getSpriteFrameByName("dice_01.png"));
	diceSprite->setPosition(ccp(tableStartPosition_x+2*tableWidth,tableStartPosition_y-tableHeight*4.5));
	addChild(diceSprite);

	diceSprite->runAction(RepeatForever::create(dice_animate));

}*/

void GameBaseScene::registerNotificationObserver()
{
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_GO,
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_BUY,
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_PAY_TOLLS,
		NULL);	
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_RANDOM_ASK_EVENT,
		NULL);	
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_BLOCK_WAY_EVENT,
		NULL);
	
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_ROUND_COUNT,
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_REST,
		NULL);	

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_STRENGTH_UP,
		NULL);
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_LOTTERY,
		NULL);
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_DIMISS_DIALOG,
		NULL);
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_STOCK,
		NULL);
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_STOCK_LAYER_DISMISS,
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_USE_SKILL,
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_GAME_OVER,
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_LOAD_GAME,
		NULL);	
}

void  GameBaseScene::showBuyLandDialog(int landTag)
{
	String showMessage = "";
	switch(landTag)
	{
	case MSG_BUY_BLANK_TAG:
		{
			showMessage = String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(),LAND_BLANK_MONEY)->getCString();
			//showMessage = "Do you want to buy the land ? need $1000 ";
			break;
		}
	case MSG_BUY_LAND_1_TAG:
		{
			showMessage = String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(),LAND_LEVEL_1_MONEY)->getCString();
			break;
		}
	case MSG_BUY_LAND_2_TAG:
		{
			showMessage = String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(),LAND_LEVEL_2_MONEY)->getCString();
			break;
		}
	}
	popDialog->setDataTag(landTag);
	popDialog->getLabelContentText()->setString(showMessage.getCString());
	popDialog->setVisible(true);

}

void GameBaseScene::buyLandCallback(Node *pNode)
{
	Util::playAudioEffect(BUTTON_CLICK_01,false);
	if(pNode->getTag() == Btn_OK_TAG)
	{		
		switch(popDialog->getDataTag())
		{
			case MSG_BUY_BLANK_TAG:
				{
					Util::playAudioEffectRandom(player1EffectVec_11, false);
					buyLand(MSG_BUY_BLANK_TAG,buy_land_x,buy_land_y,foot1Sprite,player1_building_1_tiledID,player1,PLAYER1_1_PARTICLE_PLIST);
	
					log( "need $1000 ");
					break;
				}
			case MSG_BUY_LAND_1_TAG:
				{
					Util::playAudioEffectRandom(player1EffectVec_9, false);
					buyLand(MSG_BUY_LAND_1_TAG,buy_land_x,buy_land_y,starFish1Sprite,player1_building_2_tiledID,player1,PLAYER1_1_PARTICLE_PLIST);

					log( "need $2000 ");					
					break;
				}
			case MSG_BUY_LAND_2_TAG:
				{
					Util::playAudioEffectRandom(player1EffectVec_9, false);
					buyLand(MSG_BUY_LAND_2_TAG,buy_land_x,buy_land_y,heart1Sprite,player1_building_3_tiledID,player1,PLAYER1_1_PARTICLE_PLIST);

					log( "need $3000 ");					
					break;
				}
		}
		popDialog->setVisible(false);
		NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));
		log("Btn_OK_TAG");
	}else
	{
		popDialog->setVisible(false);
		NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));
	}
	
}





void GameBaseScene::sendMSGMoveOneStep()
{
	NotificationCenter::getInstance()->postNotification(MSG_MOVE_ONE_STEP,String::createWithFormat("%d",MSG_MOVE_ONE_STEP_TAG));
}

void GameBaseScene::sendMSGPickOneToGO()
{
	NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));
}

void GameBaseScene::sendMSGPickOneToGO2(float dt)
{
	NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));
}


void  GameBaseScene::playParticle(Point point ,char* plistName)
{
	ParticleSystem* particleSystem_foot = ParticleSystemQuad::create(plistName);
	particleSystem_foot->retain();
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(particleSystem_foot->getTexture());
	batch->addChild(particleSystem_foot);	
	addChild(batch);

	particleSystem_foot->setPosition( point + ccp(tiledWidth/2,tiledHeight/2));										
	particleSystem_foot->release();
	particleSystem_foot->setAutoRemoveOnFinish(true); 

}

void GameBaseScene::receivedNotificationOMsg(Object* data)
{
	String * srcDate = (String*)data;
	Vector<String*> messageVector = Util::splitString(srcDate->getCString(),"-");
	int retMsgType = messageVector.at(0)->intValue();
	Vector<Node*> vecMenuItem = getMenu()->getChildren();
	log("received go message is: %d",retMsgType);

	if(messageVector.size()>3)
	{
		//stop_x = messageVector.at(1)->floatValue();
		//stop_y = messageVector.at(2)->floatValue();
		
		int playerTag = messageVector.at(3)->intValue();

		switch(playerTag)
		{
			case PLAYER_1_TAG:
			{
				player1->stop_x = messageVector.at(1)->floatValue();
				player1->stop_y = messageVector.at(2)->floatValue();
				break;
			}
			case PLAYER_2_TAG:
			{
				player2->stop_x = messageVector.at(1)->floatValue();
				player2->stop_y = messageVector.at(2)->floatValue();
				break;
			}
		}
		
	}

	//transferLandTag =0;


	switch(retMsgType)
	{
	case MSG_BUY_BLANK_TAG:
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerTag = messageVector.at(3)->intValue();
			
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					transferLandTag = 0;
					showBuyLandDialog(MSG_BUY_BLANK_TAG);
					break;
				}
				case PLAYER_2_TAG:
				{
					Util::playAudioEffectRandom(player2EffectVec_11, false);
					buyLand(MSG_BUY_BLANK_TAG,buy_land_x,buy_land_y,foot2Sprite,player2_building_1_tiledID,player2,PLAYER2_1_PARTICLE_PLIST);
					NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));			
					break;
				}				
			}
			break;
		}
		case MSG_BUY_LAND_1_TAG:
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerTag = messageVector.at(3)->intValue();
			
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					transferLandTag = 0;
					showBuyLandDialog(MSG_BUY_LAND_1_TAG);
					break;
				}
				case PLAYER_2_TAG:
				{
					Util::playAudioEffectRandom(player2EffectVec_9, false);
					buyLand(MSG_BUY_LAND_1_TAG,buy_land_x,buy_land_y,starFish2Sprite,player2_building_2_tiledID,player2,PLAYER2_1_PARTICLE_PLIST);
					NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));

					break;
				}				
			}
			break;
		}	
		case MSG_BUY_LAND_2_TAG:
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerTag = messageVector.at(3)->intValue();
			
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					transferLandTag = 0;
					showBuyLandDialog(MSG_BUY_LAND_2_TAG);
					break;
				}
				case PLAYER_2_TAG:
				{
					Util::playAudioEffectRandom(player2EffectVec_9, false);
					buyLand(MSG_BUY_LAND_2_TAG,buy_land_x,buy_land_y,heart2Sprite,player2_building_3_tiledID,player2,PLAYER2_1_PARTICLE_PLIST);
					NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));

					break;
				}				
			}
			break;
		}


	case MSG_GO_SHOW_TAG:
		{

			if(gameRoundCount !=0 && gameRoundCount % LOTTERY_ROUND_FREQUENTLY == 0)
			{
				scheduleOnce(schedule_selector( GameBaseScene::popPublishLottery),2.0f);
				
			}else
			{
				showGoButton();
			}
			break;
		}
	case  MSG_GO_HIDE_TAG:
		{
			/*
			for(auto it=vecMenuItem.begin();it!=vecMenuItem.end();it++)
			{
				Node* node = dynamic_cast<Node*>(*it);
				MoveBy* moveBy = MoveBy::create(0.3,ccp((node->getContentSize().width)*2,0));
				node->runAction(moveBy);
		
			}*/


			goMenuItemButton->runAction(MoveBy::create(0.3,ccp((goMenuItemButton->getContentSize().width)*2,0)));
			skillMenuItemButton->runAction(MoveBy::create(0.3,ccp((skillMenuItemButton->getContentSize().width)*2,0)));
			//showStepButton(false);
			/*
			showStepButton(!isStepLayerShow);
			isStepLayerShow = !isStepLayerShow;
			*/
			//showSkillSprites();
			
			//char temp[20];
			//memset(temp, 0, 20);
			//sprintf(temp, "dice_%02d.png",randNumber);
			//diceSprite->setSpriteFrame(diceFrameCache->getSpriteFrameByName(temp));
			
			//diceSprite->pause();
			break;
		}
	case MSG_PAY_TOLLS_1_TAG:
		{
			
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerTag = messageVector.at(3)->intValue();
			payTolls(MSG_PAY_TOLLS_1_TAG,buy_land_x,buy_land_y,playerTag);
			break;
		}
			
	case MSG_PAY_TOLLS_2_TAG:
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerTag = messageVector.at(3)->intValue();
			payTolls(MSG_PAY_TOLLS_2_TAG,buy_land_x,buy_land_y,playerTag);
			break;
		}
			
	case MSG_PAY_TOLLS_3_TAG:
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerTag = messageVector.at(3)->intValue();
			payTolls(MSG_PAY_TOLLS_3_TAG,buy_land_x,buy_land_y,playerTag);			
			break;
		}

	case MSG_ROUND_COUNT_TAG:
		{
			gameRoundCount++;
			refreshRoundDisplay();		
			break;
		}	

	case MSG_REST_TAG:
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerTag = messageVector.at(3)->intValue();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					player1->setIsMyTurn(false);									
					CocosToast::createToast(this, String::createWithFormat("%s %d %s",LanguageString::getInstance()->getLanguageString(IN_HOSPITAL_REMAIN)->getCString(),player1->restTimes,LanguageString::getInstance()->getLanguageString(RICH_DAY)->getCString())->getCString(), TOAST_SHOW_TIME,player1->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);				
					break;
				}
				case PLAYER_2_TAG:
				{
					player2->setIsMyTurn(false);
					CocosToast::createToast(this, String::createWithFormat("%s %d %s",LanguageString::getInstance()->getLanguageString(IN_HOSPITAL_REMAIN)->getCString(),player2->restTimes,LanguageString::getInstance()->getLanguageString(RICH_DAY)->getCString())->getCString(), TOAST_SHOW_TIME,player2->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);
					break;
				}				
			}
			
			break;
		}

	case MSG_RANDOM_ASK_EVENT_TAG:
		{
		
			int playerTag = messageVector.at(3)->intValue();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					doRandomAskEvent(player1);
					scheduleOnce(schedule_selector( GameBaseScene::sendMSGDealAroundLand),TOAST_SHOW_TIME);
					break;
				}
				case PLAYER_2_TAG:
				{
					doRandomAskEvent(player2);
					scheduleOnce(schedule_selector( GameBaseScene::sendMSGDealAroundLand),TOAST_SHOW_TIME);
					break;
				}				
			}
			
			break;
		}
	case MSG_STRENGTH_UP30_TAG:
		{
			doItemStrengthUp(MSG_STRENGTH_UP30_TAG, messageVector.at(3)->intValue());
			break;
		}
	case MSG_STRENGTH_UP50_TAG:
		{
			doItemStrengthUp(MSG_STRENGTH_UP50_TAG, messageVector.at(3)->intValue());
			break;
		}
	case MSG_STRENGTH_UP80_TAG:
		{
			doItemStrengthUp(MSG_STRENGTH_UP80_TAG, messageVector.at(3)->intValue());
			break;
		}
	case MSG_LOTTERY_TAG:
		{
			int playerTag = messageVector.at(3)->intValue();
			moveTag = messageVector.at(4)->intValue();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					Util::playAudioEffect(P1_need1000,false);
					
					PopupLayer* popDialogLottery = PopupLayer::create(DIALOG_BG);	
					popDialogLottery->setContentSize(CCSizeMake(Dialog_Size_Width, Dialog_Size_Height)); 
					popDialogLottery->setTitle(LanguageString::getInstance()->getLanguageString(SELECT_LOTTERY_TITLE)->getCString());
					popDialogLottery->setContentText("", 20, 60, 250);
					popDialogLottery->setPopType(LOTTERY);
					popDialogLottery->setCallbackFunc(this, callfuncN_selector(GameBaseScene::lotteryButtonCallback));
					popDialogLottery->setHasSelectedLotteryNumber(player1->lottery_vector);
					popDialogLottery->addButton(BUTTON_BG1, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(BUY_OK)->getCString(), Btn_OK_TAG);
					popDialogLottery->addButton(BUTTON_BG2, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(CANCEL)->getCString(), Btn_Cancel_TAG);
					this->addChild(popDialogLottery);				
					break;
				}
				case PLAYER_2_TAG:
				{
					int random_lottery_number = rand()%(30) + 1;
			
					repeatForCheck:
					for(int i=0;i<player2->lottery_vector.size();i++)
					{
						if(player2->lottery_vector.at(i) == random_lottery_number)
						{				
							random_lottery_number = rand()%(30) + 1;
							goto repeatForCheck;
						}
						
					}
					player2->lottery_vector.push_back(random_lottery_number);
					refreshMoneyLabel(player2,-BUY_LOTTERY_MONEY);
					if(moveTag == GOEND)
					{
						CocosToast::createToast(this, String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LOTTERY)->getCString(),BUY_LOTTERY_MONEY)->getCString(), TOAST_SHOW_TIME,player2->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGDealAroundLand2);
					}else if(moveTag ==  MOVEPASS)
					{
						CocosToast::createToast(this, String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LOTTERY)->getCString(),BUY_LOTTERY_MONEY)->getCString(), TOAST_SHOW_TIME,player2->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGMoveOneStep);
					}
					

					break;
				}				
			}




			break;
		}
	case MSG_STOCK_TAG:
		{
			int playerTag = messageVector.at(3)->intValue();
			moveTag = messageVector.at(4)->intValue();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					auto lineView = LineChart::createChart(player1,stock_pointvec1,stock_pointvec2,stock_pointvec3,stock_pointvec4,stock_pointvec5);   
					lineView->setPosition(Point(0, 0));
					lineView->moveTag = moveTag;				
					addChild(lineView);
					break;
				}
				case PLAYER_2_TAG:
				{

					doStockDeal(player2,moveTag);

					break;
				}

			}			
			break;
		}	
	case MSG_DIMISS_DIALOG_PUBLISH_LOTTERY_TAG:
		{
			//this->removeChildByTag(100);
			for(auto it=players_vector.begin();it!=players_vector.end();it++)
			{
				RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);
				refreshMoneyLabel(player,0);
			}
			showGoButton();
			break;
		}

	case MSG_STOCK_LAYER_DISMISS_TAG:
		{
			for(auto it=players_vector.begin();it!=players_vector.end();it++)
			{
				RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);
				refreshMoneyLabel(player,0);
			}
			break;
		}
	case MSG_BLOCK_WAY_EVENT_TAG:
		{
			int playerTag = messageVector.at(3)->intValue();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					doBlockWayEvent(player1);
					break;
				}
				case PLAYER_2_TAG:
				{
					doBlockWayEvent(player2);
					break;
				}				
			}
			
			break;
		}
		
	case MSG_USE_SKILL_TAG:
		{
			int playerTag = messageVector.at(3)->intValue();
			int kill_index =  messageVector.at(4)->intValue();
			int needLostStrength = messageVector.at(5)->intValue();
			int landLevel = messageVector.at(6)->intValue();
			if(playerTag == PLAYER_2_TAG)
			{
				player2->setStrength(player2->getStrength()-needLostStrength);
				refreshStrengthLabel(player2,0);
				Point pointOfGL = Util::map2GL(ccp(player2->stop_x,player2->stop_y),_map);
				switch(kill_index)
				{
					case 0:
					{
						Util::playAudioEffect(STORM_EFFECT,false);
						Util::playAudioEffectRandom(player2EffectVec_4, false);
						nextPlayerEffectVec = player1EffectVec_5;
						scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);

						//Util::playAudioEffectRandom(player1EffectVec_5, false);
						rainSprite = Sprite::createWithSpriteFrame(player2->getRainSkill()->getAnimation()->getFrames().at(0)->getSpriteFrame());
						addChild(rainSprite);
						rainSprite->setAnchorPoint(ccp(0,0));
						rainSprite->setPosition(pointOfGL+ccp(-tiledWidth/2,tiledHeight/2));
						rainSprite->runAction(Sequence::create(player2->getRainSkill(),CallFunc::create([this]()
						{
							landLayer->setTileGID(blank_land_tiledID,ccp(player2->stop_x,player2->stop_y));	
							rainSprite->removeFromParent();
							NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));
						}),NULL));
						break;
					}
					case 1:
						{
							
						}
					case 2:
						{
							 Util::playAudioEffectRandom(player2EffectVec_2, false);
							 nextPlayerEffectVec = player1EffectVec_3;
							 scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
							// Util::playAudioEffectRandom(player1EffectVec_3, false);
							transferSprite = Sprite::createWithSpriteFrame(player2->getTransfer_skill()->getAnimation()->getFrames().at(0)->getSpriteFrame());
							addChild(transferSprite);
			
							transferSprite->setAnchorPoint(ccp(0,0));
							transferSprite->setPosition(pointOfGL);
			
							transferSprite->runAction(Sequence::create(player2->getTransfer_skill(),CallFunc::create([this,landLevel]()
							{
								landLayer->setTileGID(landLevel,ccp(player2->stop_x,player2->stop_y));	
								transferSprite->removeFromParent();
								NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));
							}),NULL));

						
							break;
						}
				}

			}

			break;
		}

	case MSG_GAME_OVER_TAG:
		{
			int playerTag = messageVector.at(3)->intValue();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					Sprite* gameOver = Sprite::create("images/lose.png");
					gameOver->setPosition(winSize/2);
					addChild(gameOver);
					break;
				}
				case PLAYER_2_TAG:
				{
					playParticle(winSize/2,"images/win_particle.plist");
					Sprite* gameOver = Sprite::create("images/win.png");
					gameOver->setPosition(winSize/2);
					addChild(gameOver);
					
					break;
				}				
			}
			
			break;
		}
	
	case MSG_LOAD_GAME_TAG:
		{
			int map_level = messageVector.at(1)->intValue();
			reloadGame(map_level);			
			break;
		}
	}

}


void GameBaseScene::initStockVector(RicherPlayer* player)
{
	stockVector.clear();
	float percent = 0;
	if(stock_pointvec1.size()>1)
	{
		percent = (stock_pointvec1.at(stock_pointvec1.size()-1) - stock_pointvec1.at(stock_pointvec1.size()-2))/stock_pointvec1.at(stock_pointvec1.size()-2)*100;
	}

	stockVector.pushBack(Stock::create(800100,LanguageString::getInstance()->getLanguageString(RICH_TECHNOLOGY),stock_pointvec1.at(stock_pointvec1.size()-1),player->stockMap.at(0)->getMakedealprice(),percent,player->stockMap.at(0)->getStoreNumber()));
	
	percent = 0;
	if(stock_pointvec2.size()>1)
	{
		percent = (stock_pointvec2.at(stock_pointvec2.size()-1) - stock_pointvec2.at(stock_pointvec2.size()-2))/stock_pointvec2.at(stock_pointvec2.size()-2)*100;
	}

	stockVector.pushBack(Stock::create(800200,LanguageString::getInstance()->getLanguageString(RICH_OIL),stock_pointvec2.at(stock_pointvec1.size()-1),player->stockMap.at(1)->getMakedealprice(),percent,player->stockMap.at(1)->getStoreNumber()));

	percent = 0;
	if(stock_pointvec3.size()>1)
	{
		percent = (stock_pointvec3.at(stock_pointvec3.size()-1) - stock_pointvec3.at(stock_pointvec3.size()-2))/stock_pointvec3.at(stock_pointvec3.size()-2)*100;
	}
	stockVector.pushBack(Stock::create(800300,LanguageString::getInstance()->getLanguageString(ICBC),stock_pointvec3.at(stock_pointvec1.size()-1),player->stockMap.at(2)->getMakedealprice(),percent,player->stockMap.at(2)->getStoreNumber()));

	percent = 0;
	if(stock_pointvec4.size()>1)
	{
		percent = (stock_pointvec4.at(stock_pointvec4.size()-1) - stock_pointvec4.at(stock_pointvec4.size()-2))/stock_pointvec4.at(stock_pointvec4.size()-2)*100;
	}
	stockVector.pushBack(Stock::create(800400,LanguageString::getInstance()->getLanguageString(HUATUO_MEDICINE),stock_pointvec4.at(stock_pointvec1.size()-1),player->stockMap.at(3)->getMakedealprice(),percent,player->stockMap.at(3)->getStoreNumber()));
	
	percent = 0;
	if(stock_pointvec5.size()>1)
	{
		percent = (stock_pointvec5.at(stock_pointvec5.size()-1) - stock_pointvec5.at(stock_pointvec5.size()-2))/stock_pointvec5.at(stock_pointvec5.size()-2)*100;
	}
	stockVector.pushBack(Stock::create(800500,LanguageString::getInstance()->getLanguageString(DEMOLITION_CONSTRUCTION),stock_pointvec5.at(stock_pointvec1.size()-1),player->stockMap.at(4)->getMakedealprice(),percent,player->stockMap.at(4)->getStoreNumber()));

}

void GameBaseScene::doStockDeal(RicherPlayer* player,int moveTag)
{
	initStockVector(player);
	int selectedTag = rand()%5;
	int buyOrSellTag = rand()%2;
	if(buyOrSellTag == 1)//buy
	{
		int diffMoney = player->getMoney()-stockVector.at(selectedTag)->getNowPrice()*100;
		if(diffMoney >= 0)
		{
			Stock* s= player->stockMap.at(selectedTag);
			int storeNumber = s->getStoreNumber()+100;
			int dealPrice = (s->getMakedealprice()*s->getStoreNumber()+stockVector.at(selectedTag)->getNowPrice()*100)/(100+s->getStoreNumber());
			s->setStoreNumber(s->getStoreNumber()+100);
			s->setMakedealprice(dealPrice);		
			stockVector.at(selectedTag)->setStoreNumber(storeNumber);
			player->setMoney(diffMoney);

			if(moveTag == GOEND)
			{
				CocosToast::createToast(this, String::createWithFormat("%s %s 100 %s",LanguageString::getInstance()->getLanguageString(BUY)->getCString(),s->getStockName()->getCString(),LanguageString::getInstance()->getLanguageString(SHARES)->getCString())->getCString(), TOAST_SHOW_TIME,player2->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGDealAroundLand2);
				
			}else if(moveTag ==  MOVEPASS)
			{
				CocosToast::createToast(this, String::createWithFormat("%s %s 100 %s",LanguageString::getInstance()->getLanguageString(BUY)->getCString(),s->getStockName()->getCString(),LanguageString::getInstance()->getLanguageString(SHARES)->getCString())->getCString(), TOAST_SHOW_TIME,player2->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGMoveOneStep);
			}

		}else
		{
			if(moveTag == GOEND)
			{
				sendMSGDealAroundLand2();
			}else if(moveTag ==  MOVEPASS)
			{
				sendMSGMoveOneStep();
			}
		}

	}else if(buyOrSellTag == 0)//sell
	{

			Stock* s= player->stockMap.at(selectedTag);
			int storeNumber = s->getStoreNumber();
			if(storeNumber > 0)
			{
				player->setMoney(player->getMoney() + storeNumber * stockVector.at(selectedTag)->getNowPrice());
				s->setMakedealprice(0);
				s->setStoreNumber(0);
				if(moveTag == GOEND)
				{
					CocosToast::createToast(this, String::createWithFormat("%s %s %d %s",LanguageString::getInstance()->getLanguageString(SELL)->getCString(),s->getStockName()->getCString(),storeNumber,LanguageString::getInstance()->getLanguageString(SHARES)->getCString())->getCString(), TOAST_SHOW_TIME,player2->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGDealAroundLand2);
				
				}else if(moveTag ==  MOVEPASS)
				{
					CocosToast::createToast(this, String::createWithFormat("%s %s %d %s",LanguageString::getInstance()->getLanguageString(SELL)->getCString(),s->getStockName()->getCString(),storeNumber,LanguageString::getInstance()->getLanguageString(SHARES)->getCString())->getCString(), TOAST_SHOW_TIME,player2->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGMoveOneStep);
				}
			}else
			{
				if(moveTag == GOEND)
				{
					sendMSGDealAroundLand2();
				}else if(moveTag ==  MOVEPASS)
				{
					sendMSGMoveOneStep();
				}
			}


		}



	refreshMoneyLabel(player,0);		
}


void GameBaseScene::lotteryButtonCallback(Node *pNode)
{
	if(pNode->getTag() != -1 && pNode->getTag() != Btn_Cancel_TAG)
	{
		Util::playAudioEffect(P1_DEYIDEYITIAN, false);
		player1->lottery_vector.push_back(pNode->getTag());
		log("****lottery buy number is %d***",pNode->getTag());
		refreshMoneyLabel(player1,-BUY_LOTTERY_MONEY);
	
		if(moveTag == GOEND)
		{
			CocosToast::createToast(this, String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LOTTERY)->getCString(),BUY_LOTTERY_MONEY)->getCString(), TOAST_SHOW_TIME,player1->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGDealAroundLand2);
		}else if(moveTag ==  MOVEPASS)
		{
			CocosToast::createToast(this, String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LOTTERY)->getCString(),BUY_LOTTERY_MONEY)->getCString(), TOAST_SHOW_TIME,player1->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGMoveOneStep);
		}
		pNode->getParent()->getParent()->removeFromParent();
	}else
	{
		pNode->getParent()->getParent()->removeFromParent();
		if(moveTag == GOEND)
		{
			sendMSGDealAroundLand2();
		}else if(moveTag ==  MOVEPASS)
		{
			sendMSGMoveOneStep();
		}
	}
	

}


void GameBaseScene::doItemStrengthUp(int strengthUp,int playerTag)
{
	Util::playAudioEffect(PARTICLE_EFFECT,false);
	int strengthValue = 0;
	switch(strengthUp)
	{
	case MSG_STRENGTH_UP30_TAG:
		{
			strengthValue =30;		
			break;
		}

	case MSG_STRENGTH_UP50_TAG:
		{
			strengthValue =50;
			break;
		}

	case MSG_STRENGTH_UP80_TAG:
		{
			strengthValue =80;
			break;
		}


	}
	switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					item_strength_up->setVisible(true);
					item_strength_up->setPosition(player1->getPosition()-ccp(5,0));
					Sequence* action = Sequence::create(item_strength_up->getNormal_anmi(),
						CallFunc::create([this](){
						item_strength_up->setVisible(false);
					}
					),NULL);
					item_strength_up->runAction(action);
					CocosToast::createToast(this, 
						String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(STRENGTH_UP)->getCString(),strengthValue)->getCString(),
						TOAST_SHOW_TIME,player1->getPosition());	
					refreshStrengthLabel(player1,strengthValue);
					scheduleOnce(schedule_selector( GameBaseScene::sendMSGDealAroundLand),3.0f);
					break;
				}
				case PLAYER_2_TAG:
				{
					item_strength_up->setVisible(true);
					item_strength_up->setPosition(player2->getPosition());
										Sequence* action = Sequence::create(item_strength_up->getNormal_anmi(),
						CallFunc::create([this](){
						item_strength_up->setVisible(false);
					}
					),NULL);
					item_strength_up->runAction(action);
					//player2->runAction(player2->getStrength_up());
					CocosToast::createToast(this,
						String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(STRENGTH_UP)->getCString(),strengthValue)->getCString(),
						TOAST_SHOW_TIME,player2->getPosition());
					refreshStrengthLabel(player2,strengthValue);
					scheduleOnce(schedule_selector( GameBaseScene::sendMSGDealAroundLand),3.0f);
					//CocosToast::createToast(this, String::createWithFormat("%s %d %s",LanguageString::getInstance()->getLanguageString(IN_HOSPITAL_REMAIN)->getCString(),player2->restTimes,LanguageString::getInstance()->getLanguageString(RICH_DAY)->getCString())->getCString(), TOAST_SHOW_TIME,player2->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);
					break;
				}				
			}

}

void GameBaseScene::doRandomAskEvent(RicherPlayer* player)
{
			int randomNumber = rand()%(randomAskEventMap.size()) + 1; 
			__String * str = randomAskEventMap.at(randomNumber);

			switch(randomNumber)
			{
			case TAX_REBATES_TAG:
				{
					refreshMoneyLabel(player,10000);					
					break;
				}
			case PAY_TAXES_TAG:
				{
					if (player->getTag() == PLAYER_1_TAG)
					{
						Util::playAudioEffectRandom(player2EffectVec_13,false);
					}
					else if (player->getTag() == PLAYER_2_TAG)
					{
						Util::playAudioEffectRandom(player1EffectVec_13, false);
					}
					refreshMoneyLabel(player,-20000);
					break;
				}

			case LOSS_STRENGTH_TAG:
				{
					refreshStrengthLabel(player,-100);
					break;
				}
			case PHYSICAL_RECOVERY_TAG:
				{
					refreshStrengthLabel(player,100);
					break;
				}
			case INVESTMENT_DIVIDENDS_TAG:
				{
					Util::playAudioEffect(P1_Speaking_00181, false);
					refreshMoneyLabel(player,20000);
					break;
				}
			case INVESTMENT_LOSS_TAG:
				Util::playAudioEffect(P1_Speaking_00182, false);
				{
					refreshMoneyLabel(player,-30000);
					break;
				}
			case STORM_UP_TAG:////
				{
					//refreshMoneyLabel(player,-30000);
					player->skill_vector.at(0) ++;
					break;
				}
			case STEP_UP_TAG:
				{
					//refreshMoneyLabel(player,-30000);
					player->skill_vector.at(1) ++;
					break;
				}
			case TRANSFER_UP_TAG:
				{
					//refreshMoneyLabel(player,-30000);
					player->skill_vector.at(2) ++;
					break;
				}

			}
			CocosToast::createToast(this, str->getCString(), TOAST_SHOW_TIME,player->getPosition());
}


void GameBaseScene::sendMSGDealAroundLand(float dt)
{
	NotificationCenter::getInstance()->postNotification(MSG_AROUND_LAND,String::createWithFormat("%d",MSG_AROUND_LAND_TAG));
}

void GameBaseScene::sendMSGDealAroundLand2()
{
	NotificationCenter::getInstance()->postNotification(MSG_AROUND_LAND,String::createWithFormat("%d",MSG_AROUND_LAND_TAG));
}

void GameBaseScene::sendMSGForHandleProp(float dt)
{
	NotificationCenter::getInstance()->postNotification(MSG_HANDLE_PROP_EVENT,String::createWithFormat("%d",MSG_HANDLE_PROP_EVENT_TAG));
}

void GameBaseScene::showGoButton()
{
	/*
	Vector<Node*> vecMenuItem = getMenu()->getChildren();
	for(auto it=vecMenuItem.begin();it!=vecMenuItem.end();it++)
	{
		Node* node = dynamic_cast<Node*>(*it);
		MoveBy* moveBy = MoveBy::create(0.3,ccp(-(node->getContentSize().width)*2,0));
		node->runAction(moveBy);
		
	}*/

	goMenuItemButton->runAction(MoveBy::create(0.3,ccp(-(goMenuItemButton->getContentSize().width)*2,0)));
	skillMenuItemButton->runAction(MoveBy::create(0.3,ccp(-(skillMenuItemButton->getContentSize().width)*2,0)));

	
	//diceSprite->resume();

}

void  GameBaseScene::setWayPassToGrid()
{
	wayLayer = _map->layerNamed("way");


	Size _mapSize = wayLayer->getLayerSize(); 
	for (int j = 0;  j < _mapSize.width; j++) {  
		for (int i = 0;  i < _mapSize.height; i++) {  
			Sprite* _sp = wayLayer->tileAt(Point(j, i));  
			if (_sp) 
			{  
				float x = _sp->getPositionX();
				float y = _sp->getPositionY();
				int col = x/tiledWidth;
				int row = y/tiledHeight;
				canPassGrid[row][col] = true;
				Vec2 p = _sp->getPosition();
				wayLayerPass_vector.push_back(p);
				log("canPassGrid row=  %d ,col =%d ,canpass = %d" ,row,col,canPassGrid[row][col]);
			}  

		}  
	}  
	log("setWayPassToGrid finished");
}

void  GameBaseScene::addGoButton()
{
    Menu* menu = Menu::create();
	menu->setPosition(CCPointZero);
    setMenu(menu);
    goMenuItemButton = MenuItemImage::create("map/go_normal.png", "map/go_press.png", this, menu_selector(GameBaseScene::goButtonCallback));
 
    goMenuItemButton->setPosition(ccp(tableStartPosition_x+2*tableWidth,tableStartPosition_y-tableHeight*6));
	goMenuItemButton->setTag(goButtonTag);
	menu->addChild(goMenuItemButton);
	addChild(menu);


    skillMenuItemButton = MenuItemImage::create("images/skill_button_normal.png", "images/skill_button_pressed.png", this, menu_selector(GameBaseScene::goButtonCallback));
 
    skillMenuItemButton->setPosition(ccp(tableStartPosition_x+2*tableWidth+20,tableStartPosition_y-tableHeight*6-80));
	skillMenuItemButton->setTag(skillButtonTag);
	menu->addChild(skillMenuItemButton);

    saveMenuItemButton = MenuItemImage::create("map/save_normal.png", "map/save_pressed.png", this, menu_selector(GameBaseScene::goButtonCallback));
 
	saveMenuItemButton->setPosition(ccp(winSize.width,0));
	saveMenuItemButton->setAnchorPoint(ccp(1,0));
	saveMenuItemButton->setTag(saveButtonTag);
	menu->addChild(saveMenuItemButton);

	backItem = MenuItemImage::create("images/back_normal.png", "images/back_pressed.png",
		this, menu_selector(GameBaseScene::back));
	backItem->setAnchorPoint(ccp(0,0));
	_menu->addChild(backItem);

	backItem->setPosition(ccp(20, winSize.height - 2 * backItem->getContentSize().height));
	backItem->setScale(0.8);


	audioMenuItemButton = MenuItemImage::create(AUDIO_ON, AUDIO_OFF, this, menu_selector(GameBaseScene::goButtonCallback));

	audioMenuItemButton->setPosition(ccp(20, winSize.height - 2 * backItem->getContentSize().height - 1.5*audioMenuItemButton->getContentSize().height));
	audioMenuItemButton->setAnchorPoint(ccp(0, 0));
	audioMenuItemButton->setTag(audioButtonTag);
	audioMenuItemButton->setScale(0.8);
	bool music_on = UserDefault::getInstance()->getBoolForKey(MUSIC_ON_KEY, true);

	if (music_on)
	{
		audioMenuItemButton->unselected();
	}
	else
	{
		audioMenuItemButton->selected();
	}
	menu->addChild(audioMenuItemButton);


    step1Button = MenuItemImage::create("images/step1_normal.png", "images/step1_pressed.png", this, menu_selector(GameBaseScene::goButtonCallback));
	step1Button->setPosition(winSize/2);
	step1Button->setAnchorPoint(ccp(0.5,0));
	step1Button->setVisible(false);
	step1Button->setTag(step1_tag);
	menu->addChild(step1Button);

    step2Button = MenuItemImage::create("images/step2_normal.png", "images/step2_pressed.png", this, menu_selector(GameBaseScene::goButtonCallback));
	step2Button->setPosition(winSize/2);
	step2Button->setAnchorPoint(ccp(0.5,0));
	step2Button->setVisible(false);
	step2Button->setTag(step2_tag);
	menu->addChild(step2Button);

    step3Button = MenuItemImage::create("images/step3_normal.png", "images/step3_pressed.png", this, menu_selector(GameBaseScene::goButtonCallback));
	step3Button->setPosition(winSize/2);
	step3Button->setAnchorPoint(ccp(0.5,0));
	step3Button->setVisible(false);
	step3Button->setTag(step3_tag);
	menu->addChild(step3Button);

    step4Button = MenuItemImage::create("images/step4_normal.png", "images/step4_pressed.png", this, menu_selector(GameBaseScene::goButtonCallback));
	step4Button->setPosition(winSize/2);
	step4Button->setAnchorPoint(ccp(0.5,0));
	step4Button->setVisible(false);
	step4Button->setTag(step4_tag);
	menu->addChild(step4Button);

    step5Button = MenuItemImage::create("images/step5_normal.png", "images/step5_pressed.png", this, menu_selector(GameBaseScene::goButtonCallback));
	step5Button->setPosition(winSize/2);
	step5Button->setAnchorPoint(ccp(0.5,0));
	step5Button->setVisible(false);
	step5Button->setTag(step5_tag);
	menu->addChild(step5Button);

    step6Button = MenuItemImage::create("images/step6_normal.png", "images/step6_pressed.png", this, menu_selector(GameBaseScene::goButtonCallback));
	step6Button->setPosition(winSize/2);
	step6Button->setAnchorPoint(ccp(0.5,0));
	step6Button->setVisible(false);
	step6Button->setTag(step6_tag);
	menu->addChild(step6Button);


	skillStorm = SkillCard::createCardSprite(LanguageString::getInstance()->getLanguageString(RAIN), 
		 LanguageString::getInstance()->getLanguageString(GRADE),
		 LanguageString::getInstance()->getLanguageString(LOST_STRENGTH),
		 LanguageString::getInstance()->getLanguageString(DOWN_GRADE) ,skillSpriteCardWidth,skillSpriteCardHeight,100,-130,skillStormTag,"images/thunderstorm.png");

	addChild(skillStorm,50);

	skillStep = SkillCard::createCardSprite(LanguageString::getInstance()->getLanguageString(GOBY_HEART), 
		 LanguageString::getInstance()->getLanguageString(GRADE),
		 LanguageString::getInstance()->getLanguageString(LOST_STRENGTH),
		 LanguageString::getInstance()->getLanguageString(GOBY_HEART_INFO) ,skillSpriteCardWidth,skillSpriteCardHeight,280,-130,skillStepTag,"images/skill_step.png");
	addChild(skillStep,50);


	skillTransfer = SkillCard::createCardSprite(LanguageString::getInstance()->getLanguageString(YOURS_IS_MINE), 
		 LanguageString::getInstance()->getLanguageString(GRADE),
		 LanguageString::getInstance()->getLanguageString(LOST_STRENGTH),
		 LanguageString::getInstance()->getLanguageString(YOURS_IS_MINE_INFO) ,skillSpriteCardWidth,skillSpriteCardHeight,460,-130,skillTransferTag,"images/skill_transfer.png");
	addChild(skillTransfer,50);

	
	skillStorm->setSkillButtonCallback(this,callfuncN_selector(GameBaseScene::skillClick));


	skillStep->setSkillButtonCallback(this,callfuncN_selector(GameBaseScene::skillClick));
	skillTransfer->setSkillButtonCallback(this,callfuncN_selector(GameBaseScene::skillClick));
	isSkillLayerShow = false;
	isStepLayerShow = false;
}

void  GameBaseScene::showStepButton(bool show)
{
	if(show)
	{
		step1Button->setVisible(true);
		step2Button->setVisible(true);
		step3Button->setVisible(true);
		step4Button->setVisible(true);
		step5Button->setVisible(true);
		step6Button->setVisible(true);

		step2Button->runAction(RotateBy::create(stepSkillAnimaTime,60));
		step3Button->runAction(RotateBy::create(2*stepSkillAnimaTime,120));
		step4Button->runAction(RotateBy::create(3*stepSkillAnimaTime,180));
		step5Button->runAction(RotateBy::create(4*stepSkillAnimaTime,240));
		step6Button->runAction(RotateBy::create(5*stepSkillAnimaTime,300));

	}else
	{

		step2Button->runAction(RotateBy::create(stepSkillAnimaTime,-60));
		step3Button->runAction(RotateBy::create(2*stepSkillAnimaTime,-120));
		step4Button->runAction(RotateBy::create(3*stepSkillAnimaTime,-180));
		step5Button->runAction(RotateBy::create(4*stepSkillAnimaTime,-240));
		step6Button->runAction(RotateBy::create(5*stepSkillAnimaTime,-300));

		step6Button->runAction(Sequence::create(RotateBy::create(5*stepSkillAnimaTime,-300),CallFunc::create([this](){
			step1Button->setVisible(false);
			step2Button->setVisible(false);
			step3Button->setVisible(false);
			step4Button->setVisible(false);
			step5Button->setVisible(false);
			step6Button->setVisible(false);
		}
		),NULL));
	}
}


void GameBaseScene::skillClick(Node *pNode)
{
	Util::playAudioEffect(BUTTON_CLICK_01,false);
	int tag = pNode->getTag();
	if(tag == skillStormTag)
	{
		if(player1->stop_x  < 0)
		{
			return;
		}

		int needLostStrength = 80-player1->skill_vector.at(0)*10;
		if(player1->getStrength() >= needLostStrength)
		{
			Util::playAudioEffect(STORM_EFFECT,false);
			Util::playAudioEffectRandom(player1EffectVec_4, false);
			nextPlayerEffectVec = player2EffectVec_5;
			scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
			//Util::playAudioEffectRandom(player2EffectVec_5, false);
			showSkillSprites();
			player1->setStrength(player1->getStrength()-needLostStrength);
			refreshStrengthLabel(player1,0);

			Point pointOfGL = Util::map2GL(ccp(player1->stop_x,player1->stop_y),_map);
			rainSprite = Sprite::createWithSpriteFrame(player1->getRainSkill()->getAnimation()->getFrames().at(0)->getSpriteFrame());
			addChild(rainSprite);
			
			rainSprite->setAnchorPoint(ccp(0,0));
			rainSprite->setPosition(pointOfGL+ccp(-tiledWidth/2,tiledHeight/2));

			rainSprite->runAction(Sequence::create(player1->getRainSkill(),CallFunc::create([this]()
			{
				landLayer->setTileGID(blank_land_tiledID,ccp(player1->stop_x,player1->stop_y));	
				rainSprite->removeFromParent();
			}),NULL));
		}else
		{
			CocosToast::createToast(this,
				LanguageString::getInstance()->getLanguageString(YOUR_STRENGTH_IS_LOW)->getCString(),
				TOAST_SHOW_TIME,
				winSize/2);
		}



	}

	if(tag == skillStepTag)
	{
		showStepButton(!isStepLayerShow);
		isStepLayerShow = !isStepLayerShow;
	}

	if(tag == skillTransferTag)
	{
		if(player1->stop_x  < 0)
		{
			return;
		}

		int needLostStrength = 110-player1->skill_vector.at(2)*10;
		if(player1->getStrength() >= needLostStrength)
		{
			Util::playAudioEffectRandom(player1EffectVec_2, false);
			nextPlayerEffectVec = player2EffectVec_3;
			scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
			//Util::playAudioEffectRandom(player2EffectVec_3, false);
			int transferLand = 0;
			if(transferLandTag== MSG_PAY_TOLLS_1_TAG)
			{
				transferLand = player1_building_1_tiledID;
			}
			if(transferLandTag== MSG_PAY_TOLLS_2_TAG)
			{
				transferLand = player1_building_2_tiledID;
			}
			if(transferLandTag== MSG_PAY_TOLLS_3_TAG)
			{
				transferLand = player1_building_3_tiledID;
			}
			transferLandTag = 0;
			if(transferLand != 0)
			{
				showSkillSprites();
				player1->setStrength(player1->getStrength()-needLostStrength);
				refreshStrengthLabel(player1,0);

				Point pointOfGL = Util::map2GL(ccp(player1->stop_x,player1->stop_y),_map);
				transferSprite = Sprite::createWithSpriteFrame(player1->getTransfer_skill()->getAnimation()->getFrames().at(0)->getSpriteFrame());
				addChild(transferSprite);
			
				transferSprite->setAnchorPoint(ccp(0,0));
				transferSprite->setPosition(pointOfGL);
			
				transferSprite->runAction(Sequence::create(player1->getTransfer_skill(),CallFunc::create([this,transferLand]()
				{
					landLayer->setTileGID(transferLand,ccp(player1->stop_x,player1->stop_y));	
					transferSprite->removeFromParent();
				}),NULL));

			}
			
		}else
		{
			CocosToast::createToast(this,
				LanguageString::getInstance()->getLanguageString(YOUR_STRENGTH_IS_LOW)->getCString(),
				TOAST_SHOW_TIME,
				winSize/2);
		}
	}
}


void GameBaseScene::goButtonCallback(cocos2d::CCObject *pSender)
{
	Util::playAudioEffect(BUTTON_CLICK_01,false);
	int tag = ((Node*)pSender)->getTag();
	if(tag == goButtonTag)
	{
		if(isSkillLayerShow)
		{
			showSkillSprites();
		}
		log("go button clicked");
		randNumber = rand()%6 + 1; 
		RouteNavigation::getInstance()->getPath(player1,randNumber,canPassGrid,tiledRowsCount,tiledColsCount);
		std::vector<int> colVector = RouteNavigation::getInstance()->getPathCols_vector();
		std::vector<int> rowVector = RouteNavigation::getInstance()->getPathRow_vector();

		for(int i=0;i<rowVector.size();i++)
		{
			log(" rowVector row is %d --- colVector col is %d",rowVector[i],colVector[i]);
		}
		NotificationCenter::getInstance()->postNotification(MSG_GO,String::createWithFormat("%d",MSG_GO_HIDE_TAG));
		
		player1->startGo(rowVector,colVector);

		log("go button clicked over");
	}
	if(tag == skillButtonTag)
	{
		//String::createWithFormat("%s: %d /5",LanguageString::getInstance()->getLanguageString(GRADE),player1->skillMap.at(0));
		skillStorm->setSkillGrade(player1->skill_vector.at(0));
		skillStep->setSkillGrade(player1->skill_vector.at(1));
		skillTransfer->setSkillGrade(player1->skill_vector.at(2));

		skillStorm->setStength(80-player1->skill_vector.at(0)*10);
		skillStep->setStength(60-player1->skill_vector.at(1)*10);
		skillTransfer->setStength(110-player1->skill_vector.at(2)*10);

		showSkillSprites();

	}

	if(tag == step1_tag || tag == step2_tag || tag == step3_tag || tag == step4_tag || tag == step5_tag || tag == step6_tag)
	{

		int needLostStrength = 60-player1->skill_vector.at(1)*10;
		if(player1->getStrength() >= needLostStrength)
		{
			player1->setStrength(player1->getStrength()-needLostStrength);
			refreshStrengthLabel(player1,0);
			showSkillSprites();

			int steps = tag - stepBaseTag;
			RouteNavigation::getInstance()->getPath(player1,steps,canPassGrid,tiledRowsCount,tiledColsCount);
			std::vector<int> colVector = RouteNavigation::getInstance()->getPathCols_vector();
			std::vector<int> rowVector = RouteNavigation::getInstance()->getPathRow_vector();
			NotificationCenter::getInstance()->postNotification(MSG_GO,String::createWithFormat("%d",MSG_GO_HIDE_TAG));		
			player1->startGo(rowVector,colVector);
		}else
		{
			CocosToast::createToast(this,
				LanguageString::getInstance()->getLanguageString(YOUR_STRENGTH_IS_LOW)->getCString(),
				TOAST_SHOW_TIME,
				winSize/2);
		}

	}

	if(tag == saveButtonTag)
	{
		if(saveGame())
		{
			CocosToast::createToast(this,
				LanguageString::getInstance()->getLanguageString(SAVE_SUCESS)->getCString(),
				TOAST_SHOW_TIME,
				winSize/2);
		}else
		{
			CocosToast::createToast(this,
				LanguageString::getInstance()->getLanguageString(SAVE_FAIL)->getCString(),
				TOAST_SHOW_TIME,
				winSize/2);
		}

	}
	if (tag == audioButtonTag)
	{
		bool music_on = UserDefault::getInstance()->getBoolForKey(MUSIC_ON_KEY, true);

		if (music_on)
		{
			Util::stopAudioPlay();
			UserDefault::getInstance()->setBoolForKey(MUSIC_ON_KEY, false);
			audioMenuItemButton->selected();
		}
		else
		{
			Util::playRicherMusic(bgMusicVector.at(rand() % bgMusicVector.size()), false);
			UserDefault::getInstance()->setBoolForKey(MUSIC_ON_KEY, true);
			audioMenuItemButton->unselected();
		}

	}
	
}

void GameBaseScene::showSkillSprites()
{
		if(!isSkillLayerShow)
		{
			skillStorm->runAction(MoveBy::create(0.3,ccp(0,130)));
			skillStep->runAction(MoveBy::create(0.3,ccp(0,130)));
			skillTransfer->runAction(MoveBy::create(0.3,ccp(0,130)));
			isSkillLayerShow = true;
		}else
		{
			skillStorm->runAction(MoveBy::create(0.3,ccp(0,-130)));
			skillStep->runAction(MoveBy::create(0.3,ccp(0,-130)));
			skillTransfer->runAction(MoveBy::create(0.3,ccp(0,-130)));
			isSkillLayerShow = false;

			if(isStepLayerShow)
			{
				showStepButton(!isStepLayerShow);
				isStepLayerShow = !isStepLayerShow;
			}


		}
}

void  GameBaseScene::addRightBanner()
{
	Sprite* rightBanner = Sprite::create(RIGHT_BANNER);
	rightBanner->setAnchorPoint(ccp(0,0));
	rightBanner->setPosition( ccp(tableStartPosition_x-10, 0));
	addChild(rightBanner);
}


void GameBaseScene:: addPlayer()
{

	addPlayerInfo();

	struct timeval now; 
	gettimeofday(&now, NULL);
	unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);    //都转化为毫秒 
	srand(rand_seed);
	player1 = RicherPlayer::create(PLAYER_1_NAME,PLAYER_1_TAG,false);
	int _rand1 = rand()%(wayLayerPass_vector.size()); 
	log("rand %d" ,_rand1);
	Vec2 vec2ForPlayer1 = wayLayerPass_vector.at(_rand1);
	vec2ForPlayer1.y +=tiledHeight; 
	player1->setPosition(vec2ForPlayer1);
	player1->setAnchorPoint(ccp(0,0.5));
	int col = vec2ForPlayer1.x/tiledWidth;
	int row = vec2ForPlayer1.y/tiledHeight;
	log("player1 position row=  %d ,col = %d" ,row,col);
	log("player1 position x=  %f ,y = %f" , vec2ForPlayer1.x, vec2ForPlayer1.y);


	
	memset(money1, 0, 20);
	sprintf(money1, "$ %d",player1->getMoney());

	getPlayer1_money_label()->setString(money1);

	
	memset(strength1, 0, 20);
	sprintf(strength1, "+ %d",player1->getStrength());
	getPlayer1_strength_label()->setString(strength1);

	addChild(player1);
	players_vector.pushBack(player1);



	player2 = RicherPlayer::create(PLAYER_2_NAME,PLAYER_2_TAG,true);
	int _rand2 = rand()%(wayLayerPass_vector.size()); 
	log("rand %d" ,_rand2);
	Vec2 vec2ForPlayer2 = wayLayerPass_vector.at(_rand2);
	vec2ForPlayer2.y +=tiledHeight; 
	player2->setPosition(vec2ForPlayer2);
	player2->setAnchorPoint(ccp(0,0.5));
	int col2 = vec2ForPlayer2.x/tiledWidth;
	int row2 = vec2ForPlayer2.y/tiledHeight;
	log("player1 position row=  %d ,col = %d" ,row2,col2);
	log("player1 position x=  %f ,y = %f" , vec2ForPlayer2.x, vec2ForPlayer2.y);
	
	memset(money2, 0, 20);
	sprintf(money2, "$ %d",player1->getMoney());

	getPlayer2_money_label()->setString(money2);

	
	memset(strength2, 0, 20);
	sprintf(strength2, "+ %d",player1->getStrength());
	getPlayer2_strength_label()->setString(strength2);
	addChild(player2);
	players_vector.pushBack(player2);


	/* test player is go normal
	player3 = RicherPlayer::create("player3",PLAYER_2_TAG,true);
	int _rand3 = rand()%(wayLayerPass_vector.size()); 
	log("rand %d" ,_rand3);
	Vec2 vec2ForPlayer3 = wayLayerPass_vector.at(_rand3);
	vec2ForPlayer3.y +=tiledHeight; 
	player3->setPosition(vec2ForPlayer3);
	player3->setAnchorPoint(ccp(0,0.5));

	addChild(player3);
	players_vector.pushBack(player3);
	*/
	
}


void GameBaseScene:: addPlayerInfo()
{
	
	Sprite* player1_logo = Sprite::create(PLAYER_ME);
	player1_logo->setPosition(tableStartPosition_x+tableWidth/2,tableStartPosition_y-tableHeight);
	addChild(player1_logo);


	player1_money_label = LabelTTF::create();
	player1_money_label->setString("$");
	player1_money_label->setAnchorPoint(ccp(0,0.5));
	player1_money_label->setFontSize(FONT_SIZE);
	player1_money_label->setPosition(tableStartPosition_x+tableWidth,tableStartPosition_y-tableHeight/2);
	addChild(player1_money_label);

	player1_strength_label = LabelTTF::create();
	player1_strength_label->setString("+");
	player1_strength_label->setAnchorPoint(ccp(0,0.5));
	player1_strength_label->setFontSize(FONT_SIZE);
	player1_strength_label->setPosition(tableStartPosition_x+tableWidth,tableStartPosition_y-tableHeight/2*3);
	addChild(player1_strength_label);

	Sprite* player2_logo = Sprite::create(PLAYER_ENEMY1);
	player2_logo->setPosition(tableStartPosition_x+tableWidth/2,tableStartPosition_y-3*tableHeight);
	addChild(player2_logo);

	player2_money_label = LabelTTF::create();
	player2_money_label->setString("$");
	player2_money_label->setAnchorPoint(ccp(0,0.5));
	player2_money_label->setFontSize(FONT_SIZE);
	player2_money_label->setPosition(tableStartPosition_x+tableWidth,tableStartPosition_y-tableHeight/2*5);
	addChild(player2_money_label);

	player2_strength_label = LabelTTF::create();
	player2_strength_label->setString("+");
	player2_strength_label->setAnchorPoint(ccp(0,0.5));
	player2_strength_label->setFontSize(FONT_SIZE);
	player2_strength_label->setPosition(tableStartPosition_x+tableWidth,tableStartPosition_y-tableHeight/2*7);
	addChild(player2_strength_label);
}


void GameBaseScene:: drawTable(int playerNumber)
{
	auto draw = DrawNode::create();
	this->addChild(draw);

	for(int i=0;i<playerNumber;i++)
	{
		draw->drawSegment(Vec2(tableStartPosition_x,tableStartPosition_y-2*i*tableHeight), 
			Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y-2*i*tableHeight), 1, 
			Color4F(0, 1, 0, 1));

		draw->drawSegment(Vec2(tableStartPosition_x,tableStartPosition_y - 2*(i+1)*tableHeight), 
			Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y - 2*(i+1)*tableHeight), 1, 
			Color4F(0, 1, 0, 1));

		draw->drawSegment(Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y - tableHeight-2*i*tableHeight), 
			Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y - tableHeight-2*i*tableHeight), 1, 
			Color4F(0, 1, 0, 1));

		draw->drawSegment(Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y -2*i*tableHeight), 
			Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y -2* tableHeight-2*i*tableHeight), 1, 
			Color4F(0, 1, 0, 1));
	}
}


void GameBaseScene::onExit()
{

	CC_SAFE_DELETE(canPassGrid);
	//dice_animate->release();
	scaleby1ForBuyLand->release();
	scaleby2ForBuyLand->release();	
	landFadeOut->release();
	landFadeIn ->release();
	Layer::onExit();

}

RicherPlayer* GameBaseScene::getPlayerByTiled(float x,float y)
{
	int gid = landLayer->getTileGIDAt(ccp(x,y));
	if(gid == player1_building_1_tiledID || gid == player1_building_2_tiledID || gid == player1_building_3_tiledID)
		{
			return player1;
		}
	if(gid == player2_building_1_tiledID || gid == player2_building_2_tiledID || gid == player2_building_3_tiledID)
		{
			return player2;
		}
}

void  GameBaseScene::refreshMoneyLabel(RicherPlayer* player,int money)
{
	int tag = player->getTag();
	player->setMoney(player->getMoney()+ money);

	if(tag == PLAYER_1_TAG)
	{		
		memset(money1, 0, 20);
		sprintf(money1, "$ %d",player->getMoney());
		getPlayer1_money_label()->setString(money1);
	}
	if(tag == PLAYER_2_TAG)
	{
		memset(money2, 0, 20);
		sprintf(money2, "$ %d",player->getMoney());
		getPlayer2_money_label()->setString(money2);
	}
}



void  GameBaseScene::refreshStrengthLabel(RicherPlayer* player,int strength)
{
	int tag = player->getTag();
	int totalStrength = player->getStrength()+ strength;
	if(totalStrength > 100) totalStrength =100;
	if(totalStrength < 0) totalStrength = 0;
	player->setStrength(totalStrength);

	if(tag == PLAYER_1_TAG)
	{		
		memset(strength1, 0, 20);
		sprintf(strength1, "+ %d",player->getStrength());
		getPlayer1_strength_label()->setString(strength1);		
	}
	if(tag == PLAYER_2_TAG)
	{
		memset(strength2, 0, 20);
		sprintf(strength2, "+ %d",player->getStrength());
		getPlayer2_strength_label()->setString(strength2);
	}
}


void GameBaseScene::payTolls(int payTag,float x,float y ,int playerTag)
{
	
			int money =0;
	        if(payTag == MSG_PAY_TOLLS_1_TAG)
			{
				money = LAND_BLANK_MONEY;
			}
		   if(payTag == MSG_PAY_TOLLS_2_TAG)
			{
				money = LAND_LEVEL_1_MONEY;
			}
			if(payTag == MSG_PAY_TOLLS_3_TAG)
			{
				money = LAND_LEVEL_2_MONEY;
			}
			
			displayVector.clear();

			RicherPlayer* landOwner = getPlayerByTiled(buy_land_x,buy_land_y);
			
				
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					Util::playAudioEffectRandom(player1EffectVec_1, false);
					int retMoney = displayArea(x,y,player1,player2_building_1_tiledID,player2_building_2_tiledID,player2_building_3_tiledID);
					if(landOwner->restTimes > 0)
					{
						Util::playAudioEffectRandom(player1EffectVec_10, false);
						CocosToast::createToast(this, LanguageString::getInstance()->getLanguageString(IN_HOSPITAL)->getCString(), TOAST_SHOW_TIME,player1->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);
						return;
					}
					refreshMoneyLabel(landOwner,money + retMoney);
					refreshMoneyLabel(player1,-(money + retMoney));
					CocosToast::createToast(this, String::createWithFormat("+%d",money + retMoney)->getCString(), TOAST_SHOW_TIME+1,landOwner->getPosition());
					CocosToast::createToast(this, String::createWithFormat("-%d",money + retMoney)->getCString(), TOAST_SHOW_TIME,player1->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);
					transferLandTag = payTag;
					nextPlayerEffectVec = player2EffectVec_8;
					scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
					//Util::playAudioEffectRandom(player2EffectVec_8, false);
					
					break;
				}
				case PLAYER_2_TAG:
				{
					Util::playAudioEffectRandom(player2EffectVec_1, false);
					int retMoney = displayArea(x,y,player2,player1_building_1_tiledID,player1_building_2_tiledID,player1_building_3_tiledID);
					if(landOwner->restTimes > 0)
					{
						Util::playAudioEffectRandom(player2EffectVec_10, false);
						CocosToast::createToast(this, LanguageString::getInstance()->getLanguageString(IN_HOSPITAL)->getCString(), TOAST_SHOW_TIME,player2->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);
						return;
					}
					refreshMoneyLabel(landOwner,money + retMoney);
					refreshMoneyLabel(player2,-(money + retMoney));
					CocosToast::createToast(this, String::createWithFormat("+%d",money + retMoney)->getCString(), TOAST_SHOW_TIME+1,landOwner->getPosition());
					CocosToast::createToast(this, String::createWithFormat("-%d",money + retMoney)->getCString(), TOAST_SHOW_TIME,player2->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);
					nextPlayerEffectVec = player1EffectVec_8;
					scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
					//Util::playAudioEffectRandom(player1EffectVec_8, false);
					break;
				}				
			}
}

void GameBaseScene::buyLand(int buyTag,float x,float y ,Sprite* landSprite,int landLevel,RicherPlayer* player ,char* particlelistName)
{
			int money =0;

	        if(buyTag == MSG_BUY_BLANK_TAG)
			{
				money = LAND_BLANK_MONEY;				
			}
		   if(buyTag == MSG_BUY_LAND_1_TAG)
			{
				money = LAND_LEVEL_1_MONEY;
			}
			if(buyTag == MSG_BUY_LAND_2_TAG)
			{
				money = LAND_LEVEL_2_MONEY;
			}

			Point pointOfGL = Util::map2GL(ccp(x,y),GameBaseScene::_map);
					
			landSprite->setVisible(true);
			landSprite->setPosition(pointOfGL);
			Point pointOfMap = ccp(x,y);
			landSprite->runAction(Sequence::create(scaleby1ForBuyLand, scaleby2ForBuyLand,CallFunc::create([this,pointOfMap,pointOfGL,landSprite,landLevel,x,y,player,money,particlelistName]()
				{
					playParticle(pointOfGL,particlelistName);
					landSprite->setVisible(false);
					landLayer->setTileGID(landLevel,ccp(x,y));
					refreshMoneyLabel(player,-money);				
				}),NULL));

}

int GameBaseScene::displayArea(float x,float y,RicherPlayer* player,int building_1_tiledID,int building_2_tiledID,int building_3_tiledID)
{
	Util::playAudioEffect(BLOCK_THE_WAY,false);
	int sumMoney =0;
	float retX = Util::GL2map(player->getPosition(),_map).x;
	if(x == retX)
	{
		float leftX  = x - 1;
		float rightX = x + 1;
		int leftGID = landLayer->getTileGIDAt(ccp(leftX,y));
		int rightGID = landLayer->getTileGIDAt(ccp(rightX,y));
		displayVector.pushBack(landLayer->getTileAt(ccp(x,y)));
		while(leftGID != 0 && (leftGID == building_1_tiledID || leftGID == building_2_tiledID || leftGID == building_3_tiledID))
		{
			if(leftGID == building_1_tiledID)
			{
				sumMoney += LAND_BLANK_MONEY;
			}
			if(leftGID == building_2_tiledID)
			{
				sumMoney += LAND_LEVEL_1_MONEY;
			}
			if(leftGID == building_3_tiledID)
			{
				sumMoney += LAND_LEVEL_2_MONEY;
			}
			displayVector.pushBack(landLayer->getTileAt(ccp(leftX,y)));
			leftX -= 1;
			leftGID = landLayer->getTileGIDAt(ccp(leftX,y));

			if(leftGID == 0)
			{
				break;
			}
			log("leftGID: %d" ,leftGID);
		}
		while(rightGID != 0 && (rightGID == building_1_tiledID || rightGID == building_2_tiledID || rightGID == building_3_tiledID))
		{
			if(rightGID == building_1_tiledID)
			{
				sumMoney += LAND_BLANK_MONEY;
			}
			if(rightGID == building_2_tiledID)
			{
				sumMoney += LAND_LEVEL_1_MONEY;
			}
			if(rightGID == building_3_tiledID)
			{
				sumMoney += LAND_LEVEL_2_MONEY;
			}
			displayVector.pushBack(landLayer->getTileAt(ccp(rightX,y)));
			rightX += 1;
			rightGID = landLayer->getTileGIDAt(ccp(rightX,y));

			if(rightGID == 0)
			{
				break;
			}
			log("rightGID: %d" ,rightGID);
		}					
	}

	float retY = Util::GL2map(player->getPosition(),_map).y ;
	if(y == retY)
	{
		float upY  = y - 1;
		float downY = y + 1;
		int upGID = landLayer->getTileGIDAt(ccp(x,upY));
		int downGID = landLayer->getTileGIDAt(ccp(x,downY));
		displayVector.pushBack(landLayer->getTileAt(ccp(x,y)));
		while(upGID != 0 && (upGID == building_1_tiledID || upGID == building_2_tiledID || upGID == building_3_tiledID))
		{
			if(upGID == building_1_tiledID)
			{
				sumMoney += LAND_BLANK_MONEY;
			}
			if(upGID == building_2_tiledID)
			{
				sumMoney += LAND_LEVEL_1_MONEY;
			}
			if(upGID == building_3_tiledID)
			{
				sumMoney += LAND_LEVEL_2_MONEY;
			}
			displayVector.pushBack(landLayer->getTileAt(ccp(x,upY)));
			upY -= 1;
			upGID = landLayer->getTileGIDAt(ccp(x,upY));

			if(upGID == 0)
			{
				break;
			}
			log("leftGID: %d" ,upGID);
		}
		while(downGID != 0 && (downGID == building_1_tiledID || downGID == building_2_tiledID || downGID == building_3_tiledID))
		{
			if(downGID == building_1_tiledID)
			{
				sumMoney += LAND_BLANK_MONEY;
			}
			if(downGID == building_2_tiledID)
			{
				sumMoney += LAND_LEVEL_1_MONEY;
			}
			if(downGID == building_3_tiledID)
			{
				sumMoney += LAND_LEVEL_2_MONEY;
			}
			displayVector.pushBack(landLayer->getTileAt(ccp(x,downY)));
			downY += 1;
			downGID = landLayer->getTileGIDAt(ccp(x,downY));
			
			if(downGID == 0)
			{
				break;
			}
			log("rightGID: %d" ,downGID);
		}					
	}
	for(auto it=displayVector.begin();it!=displayVector.end();it++ )
	{					
		(Sprite*)(*it)->runAction(Sequence::create(landFadeOut->clone(),landFadeIn->clone(),NULL));
	}
	return sumMoney;
}


bool GameBaseScene::reloadGame(int map_level)
{
	auto path = FileUtils::getInstance()->getWritablePath();
	switch(map_level)
	{
	case 1:
		{
			path.append("beach_save.json");
			break;
		}
	case 2:
		{
			path.append("sea_save.json");
			break;
		}
	case 3:
		{
			path.append("snow_save.json");
			break;
		}

	}
	//*** 读取 json 文件 ***
	rapidjson::Document readdoc;
	bool bRet = false;
	ssize_t size = 0;
	std::string load_str;

	// getFileData 如果不指定，读取根目录是 Resource 文件夹
	unsigned char* titlech = FileUtils::getInstance()->getFileData(path, "r", &size);
	load_str = std::string((const char*)titlech,size);


	readdoc.Parse<0>(load_str.c_str());	
	if(readdoc.HasParseError())
	{
		CCLOG("GetParseError%s\n", readdoc.GetParseError());
	}

	if(!readdoc.IsObject())
		return 0;

	//回合数载入
	rapidjson::Value& _gameRoundCount = readdoc["gameRoundCount"];
	gameRoundCount = _gameRoundCount.GetInt();
	refreshRoundDisplay();

	//土地等级载人
	rapidjson::Value& _landlayer = readdoc["landlayer"];
	if(_landlayer.IsArray())
	{
		for(int i=0; i<_landlayer.Capacity(); i++)
		{
			rapidjson::Value& arraydoc = _landlayer[i];

			int x = arraydoc["x"].GetInt();
			CCLOG("x:%d", x);
			int y = arraydoc["y"].GetInt();
			CCLOG("y:%d", y);
			int gid = arraydoc["gid"].GetInt();
			CCLOG("gid:%d", gid);

			landLayer->setTileGID(gid,ccp(x,y));

		}
	}

	//人物载人
	rapidjson::Value& _players = readdoc["players"];
	if(_players.IsArray())
	{
		for(int i=0; i<_players.Capacity(); i++)
		{
			rapidjson::Value& arraydoc = _players[i];

			RicherPlayer* _richerPY = players_vector.at(i);

			int _restTimes = arraydoc["restTimes"].GetInt();	
			float _playerPositionX = arraydoc["playerPosition_x"].GetDouble();	
			float _playerPositionY = arraydoc["playerPosition_y"].GetDouble();
			int _stop_x = arraydoc["stop_x"].GetInt();			
			int _stop_y = arraydoc["stop_y"].GetInt();			
			int _money = arraydoc["money"].GetInt();
			int _strength = arraydoc["strength"].GetInt();
			int _comeFromeRow = arraydoc["comeFromeRow"].GetInt();
			int _comeFromCol = arraydoc["comeFromCol"].GetInt();
			bool _isMyTurn = arraydoc["isMyTurn"].GetBool();
			const char* _skill = arraydoc["skill"].GetString();
			const char* _lottery = arraydoc["lottery"].GetString();

			Vector<String*> lotteryVector = Util::splitString(_lottery,"_");
			for(int i=0;i<lotteryVector.size();i++ )
			{
				_richerPY->lottery_vector.push_back(lotteryVector.at(i)->intValue());
			}

			_richerPY->restTimes = _restTimes;
			_richerPY->setPosition(ccp(_playerPositionX,_playerPositionY));
			_richerPY->setComeFromeRow(_comeFromeRow);
			_richerPY->setComeFromCol(_comeFromCol);
			_richerPY->setIsMyTurn(_isMyTurn);
			_richerPY->stop_x = _stop_x;
			_richerPY->stop_y = _stop_y;
			_richerPY->setMoney(_money);
			_richerPY->setStrength(_strength);

			Vector<String*> skillVs = Util::splitString(_skill,"-");
			_richerPY->skill_vector.at(0) = skillVs.at(0)->intValue();
			_richerPY->skill_vector.at(1) = skillVs.at(1)->intValue();
			_richerPY->skill_vector.at(2) = skillVs.at(2)->intValue();
			refreshMoneyLabel(_richerPY,0);
			refreshStrengthLabel(_richerPY,0);

		}
	}

	//股票载入

	for(int i=0; i<players_vector.size(); i++)
	{
		RicherPlayer* _richerPY = players_vector.at(i);

		rapidjson::Value& _stocks = _players[i]["stocks"];
		if(_stocks.IsArray())
		{
			for(int i=0; i<_stocks.Capacity(); i++)
			{
				rapidjson::Value& arraydoc = _stocks[i];
				int _stockCode = arraydoc["stockCode"].GetInt();	
				int _makedealprice = arraydoc["makedealprice"].GetInt();			
				int _storeNumber = arraydoc["storeNumber"].GetInt();	
				_richerPY->stockMap.at(i)->setMakedealprice(_makedealprice);
				_richerPY->stockMap.at(i)->setStoreNumber(_storeNumber);
			}
		}

	}


	//sendMSGPickOneToGO();
    return 0;
}


bool GameBaseScene::saveGame()
{

	 //*** 生成 json 文件，存储在 getWritablePath 文件夹下 ***
	rapidjson::Document writedoc;
	writedoc.SetObject();
	rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
	rapidjson::Value players(rapidjson::kArrayType);
	writedoc.AddMember("map_level", map_level, allocator);
	writedoc.AddMember("gameRoundCount", gameRoundCount, allocator);

	int playerNumber=1;
	
	rapidjson::Value player1_json(rapidjson::kObjectType);
	rapidjson::Value player2_json(rapidjson::kObjectType);
	rapidjson::Value player3_json(rapidjson::kObjectType);


	for(auto it=players_vector.begin();it!=players_vector.end();it++)
	{
		RicherPlayer* richerPlayer = dynamic_cast<RicherPlayer*>(*it);
		switch(playerNumber)
		{
		case 1:
			{
				// json object 格式添加 “名称/值” 对
				player1_json.AddMember("playerTag", richerPlayer->getTag(), allocator);
				player1_json.AddMember("playerPosition_x", richerPlayer->getPosition().x, allocator);
				player1_json.AddMember("playerPosition_y", richerPlayer->getPosition().y, allocator);
				 player1_json.AddMember("restTimes", richerPlayer->restTimes, allocator);
				 player1_json.AddMember("stop_x", richerPlayer->stop_x, allocator);
				 player1_json.AddMember("stop_y", richerPlayer->stop_y, allocator);

				 player1_json.AddMember("money", richerPlayer->getMoney(), allocator);
				 player1_json.AddMember("strength", richerPlayer->getStrength(), allocator);

				 player1_json.AddMember("comeFromeRow", richerPlayer->getComeFromeRow(), allocator);
				 player1_json.AddMember("comeFromCol", richerPlayer->getComeFromCol(), allocator);
				 player1_json.AddMember("isMyTurn", richerPlayer->getIsMyTurn(), allocator);

				 player1_json.AddMember("skill", String::createWithFormat("%d-%d-%d",richerPlayer->skill_vector.at(0),richerPlayer->skill_vector.at(1),richerPlayer->skill_vector.at(2))->getCString(), allocator);
		
				 std::string tempstr;
				 tempstr = "";
				 for(auto i=0;i<richerPlayer->lottery_vector.size();i++)
				 {
					 tempstr.append(String::createWithFormat("%02d",richerPlayer->lottery_vector.at(i))->getCString()).append("_");
				  }
				 player1_json.AddMember("lottery", String::createWithFormat("%s",tempstr.c_str())->getCString(), allocator);

				 rapidjson::Value stocks(rapidjson::kArrayType);
				 for(auto i=0;i<richerPlayer->stockMap.size();i++)
				{
					 rapidjson::Value stock(rapidjson::kObjectType);
					 stock.AddMember("stockCode", richerPlayer->stockMap.at(i)->getCode(), allocator);
					 stock.AddMember("makedealprice", richerPlayer->stockMap.at(i)->getMakedealprice(), allocator);
					 stock.AddMember("storeNumber",richerPlayer->stockMap.at(i)->getStoreNumber(), allocator);
					 stocks.PushBack(stock, allocator);
				 }

				 player1_json.AddMember("stocks",stocks,allocator);
				 // json 加入数组
				 players.PushBack(player1_json, allocator);
				 break;
			}
		case 2:
			{
				 player2_json.AddMember("playerTag", richerPlayer->getTag(), allocator);
				 player2_json.AddMember("playerPosition_x", richerPlayer->getPosition().x, allocator);
				 player2_json.AddMember("playerPosition_y", richerPlayer->getPosition().y, allocator);
				 player2_json.AddMember("restTimes", richerPlayer->restTimes, allocator);
				 player2_json.AddMember("stop_x", richerPlayer->stop_x, allocator);
				 player2_json.AddMember("stop_y", richerPlayer->stop_y, allocator);

				 player2_json.AddMember("money", richerPlayer->getMoney(), allocator);
				 player2_json.AddMember("strength", richerPlayer->getStrength(), allocator);

				 player2_json.AddMember("comeFromeRow", richerPlayer->getComeFromeRow(), allocator);
				 player2_json.AddMember("comeFromCol", richerPlayer->getComeFromCol(), allocator);
				 player2_json.AddMember("isMyTurn", richerPlayer->getIsMyTurn(), allocator);

				 player2_json.AddMember("skill", String::createWithFormat("%d-%d-%d",richerPlayer->skill_vector.at(0),richerPlayer->skill_vector.at(1),richerPlayer->skill_vector.at(2))->getCString(), allocator);
				
				 std::string tempstr;
				 tempstr = "";
				 for(auto i=0;i<richerPlayer->lottery_vector.size();i++)
				 {
					 tempstr.append(String::createWithFormat("%02d",richerPlayer->lottery_vector.at(i))->getCString()).append("_");
				  }
				 player2_json.AddMember("lottery",String::createWithFormat("%s",tempstr.c_str())->getCString(), allocator);

				 rapidjson::Value stocks(rapidjson::kArrayType);
				 for(auto i=0;i<richerPlayer->stockMap.size();i++)
				{
					 rapidjson::Value stock(rapidjson::kObjectType);
					 stock.AddMember("stockCode", richerPlayer->stockMap.at(i)->getCode(), allocator);
					 stock.AddMember("makedealprice", richerPlayer->stockMap.at(i)->getMakedealprice(), allocator);
					 stock.AddMember("storeNumber",richerPlayer->stockMap.at(i)->getStoreNumber(), allocator);
					 stocks.PushBack(stock, allocator);
				 }

				 player2_json.AddMember("stocks",stocks,allocator);
				 players.PushBack(player2_json, allocator);
				 break;
			}
		case 3:
			{
				 player3_json.AddMember("playerTag", richerPlayer->getTag(), allocator);
				 player3_json.AddMember("playerPosition_x", richerPlayer->getPosition().x, allocator);
				 player3_json.AddMember("playerPosition_y", richerPlayer->getPosition().y, allocator);
				 player3_json.AddMember("restTimes", richerPlayer->restTimes, allocator);
				 player3_json.AddMember("stop_x", richerPlayer->stop_x, allocator);
				 player3_json.AddMember("stop_y", richerPlayer->stop_y, allocator);

				 player3_json.AddMember("money", richerPlayer->getMoney(), allocator);
				 player3_json.AddMember("strength", richerPlayer->getStrength(), allocator);

				 player3_json.AddMember("comeFromeRow", richerPlayer->getComeFromeRow(), allocator);
				 player3_json.AddMember("comeFromCol", richerPlayer->getComeFromCol(), allocator);
				 player3_json.AddMember("isMyTurn", richerPlayer->getIsMyTurn(), allocator);

				 player3_json.AddMember("skill", String::createWithFormat("%d-%d-%d",richerPlayer->skill_vector.at(0),richerPlayer->skill_vector.at(1),richerPlayer->skill_vector.at(2))->getCString(), allocator);
				
				 std::string tempstr;
				 tempstr = "";
				 for(auto i=0;i<richerPlayer->lottery_vector.size();i++)
				 {
					 tempstr.append(String::createWithFormat("%02d",richerPlayer->lottery_vector.at(i))->getCString()).append("_");
				  }
				 player3_json.AddMember("lottery",String::createWithFormat("%s",tempstr.c_str())->getCString(), allocator);

				 rapidjson::Value stocks(rapidjson::kArrayType);
				 for(auto i=0;i<richerPlayer->stockMap.size();i++)
				{
					 rapidjson::Value stock(rapidjson::kObjectType);
					 stock.AddMember("stockCode", richerPlayer->stockMap.at(i)->getCode(), allocator);
					 stock.AddMember("makedealprice", richerPlayer->stockMap.at(i)->getMakedealprice(), allocator);
					 stock.AddMember("storeNumber",richerPlayer->stockMap.at(i)->getStoreNumber(), allocator);
					 stocks.PushBack(stock, allocator);
				 }

				 player3_json.AddMember("stocks",stocks,allocator);
				 players.PushBack(player3_json, allocator);
				 break;
			}


		}


		playerNumber++;
	}
	 writedoc.AddMember("players", players, allocator);

	// landLayer;


	 rapidjson::Value landlayerJson(rapidjson::kArrayType);
	Size _landLayerSize = landLayer->getLayerSize(); 
	for (int j = 0;  j < _landLayerSize.width; j++) {  
		for (int i = 0;  i < _landLayerSize.height; i++) {  
			Sprite* _sp = landLayer->tileAt(Point(j, i));  
			if (_sp) 
			{  
				rapidjson::Value landJson(rapidjson::kObjectType);
				int gid = landLayer->getTileGIDAt(Point(j, i));
				landJson.AddMember("x", j, allocator);
				landJson.AddMember("y", i, allocator);
				landJson.AddMember("gid",gid, allocator);
				landlayerJson.PushBack(landJson, allocator);
			}  

		}  
	}

	writedoc.AddMember("landlayer", landlayerJson, allocator);



   StringBuffer buffer;
	  rapidjson::Writer<StringBuffer> writer(buffer);
	  writedoc.Accept(writer);

	  auto path = FileUtils::getInstance()->getWritablePath();
	  path.append(saveJsonName);
	  FILE* file = fopen(path.c_str(), "wb");
	  if(file)
	  {
		fputs(buffer.GetString(), file);
		fclose(file);
	  }
	CCLOG("%s",buffer.GetString());
  return true;

}