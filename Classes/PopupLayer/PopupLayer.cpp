#include "PopupLayer.h"
#include "SeaScene.h"
#include "BeachScene.h"
#include "SnowScene.h"

PopupLayer::PopupLayer():
m__pMenu(NULL)
, m_contentPadding(0)
, m_contentPaddingTop(0)
, m_callbackListener(NULL)
, m_callback(NULL)
, m__sfBackGround(NULL)
, m__s9BackGround(NULL)
, m__ltContentText(NULL)
, m__ltTitle(NULL)
{
    
}

PopupLayer::~PopupLayer()
{
    CC_SAFE_RELEASE(m__pMenu);
    CC_SAFE_RELEASE(m__sfBackGround);
    CC_SAFE_RELEASE(m__ltContentText);
    CC_SAFE_RELEASE(m__ltTitle);
    CC_SAFE_RELEASE(m__s9BackGround);
}

bool PopupLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
		this->setContentSize(CCSizeZero);
        // 初始化需要的 Menu
        Menu* menu = Menu::create();
        menu->setPosition(CCPointZero);
        setMenuButton(menu);
		lottery_selected = 0;
		setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	    auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);

	    listener->onTouchBegan = [](Touch *t,Event *e){
			CCLog("PopupLayer touch");
           return true;
    };
		// _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}


PopupLayer* PopupLayer::create(const char *backgroundImage)
{
    PopupLayer* ml = PopupLayer::create();
    ml->setSpriteBackGround(Sprite::create(backgroundImage));
    ml->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
    return ml;
}

void PopupLayer::setPopType(POP_TYPE type)
{
	pop_type = type;
}

void PopupLayer::setTitle(const char *title, int fontsize)
{
    LabelTTF* ltfTitle = LabelTTF::create(title, "", fontsize);
    setLabelTitle(ltfTitle);
}

void PopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop)
{
    LabelTTF* ltf = LabelTTF::create(text, "", fontsize);
    setLabelContentText(ltf);
    m_contentPadding = padding;
    m_contentPaddingTop = paddingTop;
}


void PopupLayer::setLotteryContext(Size size)
{
	//Size winSize = Director::getInstance()->getWinSize();
	Size center =(winSize - size)/2;
    //10*3的单元格
    for(int row=0; row<10; row++)
    {
        for(int col=0; col<3; col++)
        {			
			LotteryCard* card = LotteryCard::createCardSprite((row+1)+ col*10, 40,40, center.width+20+row*(size.width/11), (winSize.height/2+30)-40*col);
			card->setTag((row+1)+ col*10);	
			card->setBallCallbackFunc(this,callfuncN_selector(PopupLayer::refreshBallBackGround));

			addChild(card);
			lotteryVector.pushBack(card);
			
			for(int i=0;i<selected_number_vector.size();i++)
			{
				if(selected_number_vector.at(i) == (row+1)+ col*10)
				{				
					card->setVisible(false);
				}
			}						
        }
    }
}

void PopupLayer::setPublishLotteryContext(Size size)
{
	//添加转盘
	m_turnBg = Sprite::create("LotteryTurn/turn_bg.png");
	m_turnBg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	addChild(m_turnBg);

	//添加指针
	auto arrNor = Sprite::create("LotteryTurn/turn_arrow.png");
	arrNor->setPosition(Vec2(winSize.width / 2, winSize.height * 0.557));
	arrNor->setScale(0.5);
	addChild(arrNor);

	//添加中奖之后的简单界面
	awardLayer = LayerColor::create(Color4B(0, 0, 0, 100));
	awardLayer->setPosition(Point::ZERO);
	awardLayer->setTag(100);
	addChild(awardLayer, 10);
	awardLayer->setVisible(false);
	addPlayersInfo(size);
	
}

void PopupLayer::onTurnEnd()
{
	m_pElliRtt_1->removeFromParentAndCleanup(true);
	m_pElliRtt_2->removeFromParentAndCleanup(true);
	m_pCircle_1->removeFromParentAndCleanup(true);
	m_pCircle_2->removeFromParentAndCleanup(true);

	scheduleOnce(schedule_selector(PopupLayer::dismissFromParent), 4.0f);
	int j = 0;
	for (auto it = players_vector.begin(); it != players_vector.end(); it++)
	{
		RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);
		//player->lottery_vector.push_back(8);

		for (int i = 0; i < player->lottery_vector.size(); i++)
		{
			if (player->lottery_vector.at(i) == lottNumber)
			{
				player->setMoney(player->getMoney() + LOTTERY_WIN_MONEY);

				//弹出抽中奖品
				((LayerColor *)getChildByTag(100))->setVisible(true);
				char* pngdispaly;
				if (player->getTag() == PLAYER_1_TAG)
				{
					pngdispaly = "LotteryTurn/lottery_p1_ha.png";
				}
				if (player->getTag() == PLAYER_2_TAG)
				{
					pngdispaly = "LotteryTurn/lottery_p2_ha.png";
				}
				auto award = Sprite::create(pngdispaly);
				award->setAnchorPoint(Vec2(0.5, 0));
				award->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
				awardLayer->addChild(award);
				auto bounce = EaseBounceOut::create(MoveBy::create(2, Vec2(0, -getPositionX() * 2)));
				award->runAction(Sequence::createWithTwoActions(bounce, CallFuncN::create([=](Node * node){
					award->removeFromParentAndCleanup(true);	
					((LayerColor *)getChildByTag(100))->setVisible(false);
				})));

			}
		}
		player->lottery_vector.clear();
		j++;
	}

	Util::playAudioEffect(P1_meirendejiang,false);

}

void PopupLayer::setLoadGameContext(Size size)
{
	//Size winSize = Director::getInstance()->getWinSize();
	
	Menu* menu = Menu::create();
	menu->setPosition(CCPointZero);
  
	  auto beach_path = FileUtils::getInstance()->getWritablePath();
	  beach_path.append("beach_save.json");
	  FILE* beach_file = fopen(beach_path.c_str(), "r");
	  if(beach_file)
	  {
		beachLoadGameMenuItem = MenuItemImage::create("map/beach_load_normal.png", "map/beach_load_pressed.png", this, menu_selector(PopupLayer::loadGameButtonCallback)); 
		beachLoadGameMenuItem->setPosition(winSize/2+Size(0,120));
		beachLoadGameMenuItem->setTag(save_beach_tag);
		menu->addChild(beachLoadGameMenuItem);
		fclose(beach_file);
	  }else
	  {
		beachLoadGameMenuItem = MenuItemImage::create("map/blank.png", "map/blank.png", this, menu_selector(PopupLayer::loadGameButtonCallback));
		beachLoadGameMenuItem->setPosition(winSize/2+Size(0,120));
		menu->addChild(beachLoadGameMenuItem);
	  }





	  auto sea_path = FileUtils::getInstance()->getWritablePath();
	  sea_path.append("sea_save.json");
	  FILE* sea_file = fopen(sea_path.c_str(), "r");
	  if(sea_file)
	  {
		seaLoadGameMenuItem = MenuItemImage::create("map/sea_load_normal.png", "map/sea_load_pressed.png", this, menu_selector(PopupLayer::loadGameButtonCallback)); 
		seaLoadGameMenuItem->setPosition(winSize/2+Size(0,20));
		seaLoadGameMenuItem->setTag(save_sea_tag);
		menu->addChild(seaLoadGameMenuItem);
		fclose(sea_file);
	  }else
	  {
		seaLoadGameMenuItem = MenuItemImage::create("map/blank.png", "map/blank.png", this, menu_selector(PopupLayer::loadGameButtonCallback));
		seaLoadGameMenuItem->setPosition(winSize/2+Size(0,20));
		menu->addChild(seaLoadGameMenuItem);
	  }

	  auto snow_path = FileUtils::getInstance()->getWritablePath();
	  snow_path.append("snow_save.json");
	  FILE* snow_file = fopen(snow_path.c_str(), "r");
	  if(snow_file)
	  {
		  snowLoadGameMenuItem = MenuItemImage::create("map/snow_load_normal.png", "map/snow_load_pressed.png", this, menu_selector(PopupLayer::loadGameButtonCallback));
		snowLoadGameMenuItem->setPosition(winSize / 2 + Size(0, -80));
		snowLoadGameMenuItem->setTag(save_snow_tag);
		menu->addChild(snowLoadGameMenuItem);
		fclose(snow_file);
	  }else
	  {
		  snowLoadGameMenuItem = MenuItemImage::create("map/blank.png", "map/blank.png", this, menu_selector(PopupLayer::loadGameButtonCallback));
		  snowLoadGameMenuItem->setPosition(winSize / 2 + Size(0, -80));
		  menu->addChild(snowLoadGameMenuItem);
	  }

	addChild(menu);

}

void PopupLayer::loadGameButtonCallback(cocos2d::CCObject *pSender)
{
	
	int tag = ((Node*)pSender)->getTag();
	if(tag == save_beach_tag)
	{
		TransitionFadeBL* scene = TransitionFadeBL::create(1, BeachScene::createScene());
		Director::getInstance()->pushScene(scene);

		String * str = String::createWithFormat("%d-%d", MSG_LOAD_GAME_TAG, tag);
		NotificationCenter::getInstance()->postNotification(MSG_LOAD_GAME, str);

		log("beach load");
	}
	if(tag == save_sea_tag)
	{
		TransitionFadeBL* scene = 	TransitionFadeBL::create(1, SeaScene::createScene());
		Director::getInstance()->pushScene(scene);

		String * str = String::createWithFormat("%d-%d",MSG_LOAD_GAME_TAG,tag);
		NotificationCenter::getInstance()->postNotification(MSG_LOAD_GAME,str);	

		log("sea load");
	}
	if(tag == save_snow_tag)
	{
		TransitionFadeBL* scene = TransitionFadeBL::create(1, SnowScene::createScene());
		Director::getInstance()->pushScene(scene);

		String * str = String::createWithFormat("%d-%d", MSG_LOAD_GAME_TAG, tag);
		NotificationCenter::getInstance()->postNotification(MSG_LOAD_GAME, str);
		log("snow load");
	}
}

void PopupLayer::realRunPublishAnmi(float dt)
{
	//Util::playAudioEffect(MASHANGKAIJIANG, false);
	srand(unsigned(time(NULL)));
	lottNumber = rand() % (30) + 1;
	float angleRotate = (30 - lottNumber + 1) * 12 + 7200;
	CCLog("****lottNumberis %d :**", lottNumber);
	//auto pAction = EaseExponentialOut::create(RotateBy::create(4, Vec3(0, 0, angleZ)));
	auto pAction = EaseExponentialOut::create(RotateBy::create(6, angleRotate));
	m_turnBg->runAction(Sequence::create(pAction, CallFunc::create(CC_CALLBACK_0(PopupLayer::onTurnEnd, this)), NULL));

	//添加椭圆旋转粒子效果
	m_pElliRtt_1 = ParticleSystemQuad::create("LotteryTurn/whiteBall.plist");
	addChild(m_pElliRtt_1);
	m_pElliRtt_2 = ParticleSystemQuad::create("LotteryTurn/yellowBall.plist");
	addChild(m_pElliRtt_2);

	//椭圆旋转
	EllipseConfig config;
	config.ellipseA = 100;
	config.ellipseB = 50;
	config.cenPos = m_turnBg->getPosition();
	config.isAntiClockwise = true;
	config.startAngle = 0;
	config.selfAngle = 45;

	m_pElliRtt_1->runAction(RepeatForever::create(EllipseBy::create(2.5, config)));

	config.startAngle = 180;
	config.selfAngle = -45;

	m_pElliRtt_2->runAction(RepeatForever::create(EllipseBy::create(2.5, config)));

	//圈圈闪烁粒子效果
	m_pCircle_1 = ParticleSystemQuad::create("LotteryTurn/bigCircle.plist");
	m_pCircle_1->setPosition(m_turnBg->getPosition());
	addChild(m_pCircle_1);
	m_pCircle_1->runAction((RotateBy::create(4, angleRotate)));

	m_pCircle_2 = ParticleSystemQuad::create("LotteryTurn/smallCircle.plist");
	m_pCircle_2->setPosition(m_turnBg->getPosition());
	addChild(m_pCircle_2);
	m_pCircle_2->runAction((RotateBy::create(4, angleRotate)));
	
}

void PopupLayer::runPublishAnmi()
{
	Util::playAudioEffect(MASHANGKAIJIANG, false);
	scheduleOnce(schedule_selector( PopupLayer::realRunPublishAnmi),3.0f);
}

void PopupLayer::setPlayerVector(Vector<RicherPlayer*> _vector)
{
	for(int i=0;i<_vector.size();i++)
	{
		players_vector.pushBack(_vector.at(i));

	}
	
}

void PopupLayer::dismissFromParent(float dt)
{	
	m_turnBg->runAction(RotateBy::create(0, -(30 - lottNumber + 1) * 12));
	NotificationCenter::getInstance()->postNotification(MSG_DIMISS_DIALOG,String::createWithFormat("%d",MSG_DIMISS_DIALOG_PUBLISH_LOTTERY_TAG));
	this->setVisible(false);
}

void PopupLayer::addPlayersInfo(Size size)
{
	//Size winSiz = Director::getInstance()->getWinSize();
	Size center =(winSize-size)/2;
	int j=0;
	for(auto it=players_vector.begin();it!=players_vector.end();it++)
	{
		RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);

		//SpriteFrame* spf;
		int tag = player->getTag();
		char* playerLog;
		switch(tag)
		{
		case PLAYER_1_TAG:
			{
				playerLog = "map/player1.png";
				//spf = player->player_spriteFrameCache->getSpriteFrameByName("player1_anim_01.png");
				break;
			}
		case PLAYER_2_TAG:
			{
				playerLog = "map/player2.png";
				//spf = player->player_spriteFrameCache->getSpriteFrameByName("player2_anim_02.png");
				break;
			}
		}

		//Sprite* playerSprite = Sprite::createWithSpriteFrame(spf);
		Sprite* playerSprite = Sprite::create(playerLog);
		playerSprite->setPosition( center.width+20, (winSize.height/2+50)+j*50);
		playerSprite->setScale(0.8);
		addChild(playerSprite);
		j++;
	}
	
}


void PopupLayer::addPlayersLottery()
{
	for(int i=1;i<=30;i++)
	{
		if(this->getChildByTag(1000+i) != NULL)
		{
			this->removeChildByTag(1000+i);
		}
		
	}

	//Size winSize = Director::getInstance()->getWinSize();
	Size size = this->getContentSize();
	Size center =(winSize-size)/2;
	int j=0;
	for(auto it=players_vector.begin();it!=players_vector.end();it++)
	{
		RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);
		
		playerLotteryVector.clear();
		for(int i=0;i < player->lottery_vector.size();i++)
		{
			
			LabelTTF* labelLotteryNumber = LabelTTF::create(String::createWithFormat("%i",player->lottery_vector.at(i))->getCString(),"",15);
			labelLotteryNumber->setPosition(ccp( center.width+20+(i+1)*20, (winSize.height/2+30)+j*50));
			labelLotteryNumber->setColor(Color3B(255,100,100));
			labelLotteryNumber->setTag(1000+player->lottery_vector.at(i));
			playerLotteryVector.pushBack(labelLotteryNumber);
		}

		for(int i=0;i < playerLotteryVector.size();i++)
		{
			addChild(playerLotteryVector.at(i));	
		}
		j++;

	}
}

void PopupLayer::setHasSelectedLotteryNumber(std::vector<int> _vector)
{
	for(int i=0;i<_vector.size();i++)
	{
		selected_number_vector.push_back(_vector.at(i));
	}
	
}

void PopupLayer::refreshBallBackGround(Node *pNode)
{
	int tag2= pNode->getTag();
	
	for(auto it=lotteryVector.begin();it!=lotteryVector.end();it++)
	{
		LotteryCard* node = (LotteryCard*)(*it);
		int tag1= node->getTag();

		if(node->getTag() != pNode->getTag())
		{
			node->setUnSelected();
		}		
	}
		lottery_selected =  tag2;

		Vector<Node*> menuItemVector = getMenuButton()->getChildren();
		for(int i=0;i< getMenuButton()->getChildrenCount();i++)
		{
			if(menuItemVector.at(i)->getTag() != 0)
			{
				menuItemVector.at(i)->setTag(tag2);
				break;
			}
		}


}


void PopupLayer::setCallbackFunc(cocos2d::Object *target, SEL_CallFuncN callfun)
{
    m_callbackListener = target;
    m_callback = callfun;    
}


bool PopupLayer::addButton(const char *normalImage, const char *selectedImage, const char *title, int tag)
{
	//Size winSize = CCDirector::getInstance()->getWinSize();
    Point pCenter = ccp(winSize.width / 2, winSize.height / 2);
    
    // 创建图片菜单按钮
    MenuItemImage* menuImage = MenuItemImage::create(normalImage, selectedImage, this, menu_selector(PopupLayer::buttonCallback));
    menuImage->setTag(tag);
    menuImage->setPosition(pCenter);
    
    // 添加文字说明并设置位置

	Size imenu = menuImage->getContentSize();
    LabelTTF* ttf = LabelTTF::create(title, "", 20);
    ttf->setColor(ccc3(0, 0, 0));
    ttf->setPosition(ccp(imenu.width / 2, imenu.height / 2));
    menuImage->addChild(ttf);


    getMenuButton()->addChild(menuImage);
    return true;
}

void PopupLayer::buttonCallback(cocos2d::CCObject *pSender)
{
    Node* node = dynamic_cast<Node*>(pSender);
    CCLog("touch tag: %d", node->getTag());
    if (m_callback && m_callbackListener){
        (m_callbackListener->*m_callback)(node);
    }
   // this->removeFromParent();
}

void PopupLayer::onEnter()
{
    Layer::onEnter();
    
	//Size winSize = Director::getInstance()->getWinSize();
    Point pCenter = ccp(winSize.width / 2, winSize.height / 2);
    
    Size contentSize;
    // 设定好参数，在运行时加载
    if (getContentSize().equals(CCSizeZero)) 
	{
        getSpriteBackGround()->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(getSpriteBackGround(), 0, 0);
        contentSize = getSpriteBackGround()->getTexture()->getContentSize();
    } else {
        Scale9Sprite *background = getSprite9BackGround();
        background->setContentSize(getContentSize());
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background, 0, 0);
        contentSize = getContentSize();
    }
    
    
    // 添加按钮，并设置其位置
    this->addChild(getMenuButton());
    float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);
    
	Vector<Node*> vecArray = getMenuButton()->getChildren();

	int j=0;
	for(auto it=vecArray.begin();it!=vecArray.end();it++)
	{
		Node* node = dynamic_cast<Node*>(*it);
		node->setPosition(Point(winSize.width/2 - contentSize.width/2+btnWidth*(j+1),winSize.height/2-contentSize.height/3));
		j++;
	}

    // 显示对话框标题
    if (getLabelTitle())
	{
        getLabelTitle()->setPosition(ccpAdd(pCenter, ccp(0, contentSize.height / 2 -20)));
		getLabelTitle()->setColor(ccc3(0,0,0));
        this->addChild(getLabelTitle());
    }
    
	switch(pop_type)
	{
	case LOTTERY:
		{
			setLotteryContext(contentSize);
			break;
		}
	case LOTTERY_PUBLISH:
		{
							
			setPublishLotteryContext(contentSize);
			break;
		}
	case LOADGAME:
		{

			setLoadGameContext(contentSize);
			break;
		}
	default:
		{
		     // 显示文本内容
			if (getLabelContentText())
			{
				LabelTTF* ltf = getLabelContentText();
				ltf->setPosition(ccp(winSize.width / 2, winSize.height / 2));
				ltf->setDimensions(CCSizeMake(contentSize.width - m_contentPadding * 2, contentSize.height - m_contentPaddingTop));
				ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
				ltf->setColor(ccc3(0,0,0));
				this->addChild(ltf);
			}
		}
	}




    // 弹出效果
    Action* popupLayer = Sequence::create(ScaleTo::create(0.0, 0.0),
                                          ScaleTo::create(0.15, 1.05),
                                          ScaleTo::create(0.08, 0.95),
                                          ScaleTo::create(0.08, 1.0),
										  NULL);
    this->runAction(popupLayer);

}

void PopupLayer::onExit()
{
    
    CCLog("popup on exit.");
	//this->removeFromParent();
    Layer::onExit();
}
