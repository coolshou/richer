#include "MenuScene.h"

USING_NS_CC;


Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

    auto layer = MenuScene::create();

    scene->addChild(layer);

    return scene;

}
  
bool MenuScene::init()
{
	if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) )
    {
        return false;
    }
	visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	addBackgroundSprite();

	addMenuSprites();


    return true;
}

void MenuScene::addBackgroundSprite()
{
	Sprite* menuSpriteLogo= Sprite::create(MENU_LOGO);
	menuSpriteLogo->setPosition(ccp(visibleSize.width/2,visibleSize.height));
	menuSpriteLogo->setAnchorPoint(ccp(0.5,1));
	menuSpriteLogo->setScale(0.6f);
	addChild(menuSpriteLogo);


	Sprite* rainBowSprite= Sprite::create(RAINBOW);
	rainBowSprite->setPosition(ccp(5,visibleSize.height-20));
	rainBowSprite->setAnchorPoint(ccp(0,1));
	rainBowSprite->setScale(0.3f);
	addChild(rainBowSprite);

	MoveBy* rainBowMove = MoveBy::create(1,ccp(8,0));
	MoveBy* rainBowMoveReverse = rainBowMove->reverse();
	Sequence* rainBowAction = Sequence::create(rainBowMove,rainBowMoveReverse,NULL);
	rainBowSprite->runAction(RepeatForever::create(rainBowAction));
}


void MenuScene:: addMenuSprites()
{
	Scale9Sprite* btnNormal = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite* btnPress = Scale9Sprite::create(PRESS_MENU);

	LabelTTF* singleGameTTF = LabelTTF::create(LanguageString::getInstance()->getLanguageString(SINGLE_GAME)->getCString() ,FONT_MENU,Btn_FontSize);
	ControlButton* singleGameBtn = ControlButton::create(singleGameTTF,btnNormal);
	singleGameBtn->setBackgroundSpriteForState(btnPress, Control::State::SELECTED);

	singleGameBtn->setPosition(ccp(visibleSize.width/2,visibleSize.height-180));
	singleGameBtn->setPreferredSize(Size(Btn_Width,Btn_Height));
	singleGameBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(MenuScene::menuTouchDown),Control::EventType::TOUCH_DOWN);
	singleGameBtn->setTag(Btn_Single_Game_TAG);
	addChild(singleGameBtn);

	Scale9Sprite* btnNormal2 = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite* btnPress2 = Scale9Sprite::create(PRESS_MENU);
	LabelTTF* multiGameTTF = LabelTTF::create(LanguageString::getInstance()->getLanguageString(MULTI_GAME)->getCString(),FONT_MENU,Btn_FontSize);
	ControlButton* multiGameBtn = ControlButton::create(multiGameTTF,btnNormal2);
	multiGameBtn->setBackgroundSpriteForState(btnPress2, Control::State::HIGH_LIGHTED);

	multiGameBtn->setPosition(ccp(visibleSize.width/2,visibleSize.height-240));
	multiGameBtn->setPreferredSize(Size(Btn_Width,Btn_Height));
	multiGameBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(MenuScene::menuTouchDown),Control::EventType::TOUCH_DOWN);
	multiGameBtn->setTag(Btn_Multi_Game_TAG);
	addChild(multiGameBtn);

	Scale9Sprite* btnNormal3 = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite* btnPress3 = Scale9Sprite::create(PRESS_MENU);

	bool music_on = UserDefault::getInstance()->getBoolForKey(MUSIC_ON_KEY,true);
	LabelTTF* settingsGameTTF;
	if(music_on)
	{
		settingsGameTTF = LabelTTF::create(LanguageString::getInstance()->getLanguageString(MUSIC_ON)->getCString(),FONT_MENU,Btn_FontSize);
	}else
	{
		settingsGameTTF = LabelTTF::create(LanguageString::getInstance()->getLanguageString(MUSIC_OFF)->getCString(),FONT_MENU,Btn_FontSize);
	}
	
	ControlButton* settingsGameBtn = ControlButton::create(settingsGameTTF,btnNormal3);
	settingsGameBtn->setBackgroundSpriteForState(btnPress3, Control::State::SELECTED);

	settingsGameBtn->setPosition(ccp(visibleSize.width/2,visibleSize.height-300));
	settingsGameBtn->setPreferredSize(Size(Btn_Width,Btn_Height));
	settingsGameBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(MenuScene::menuTouchDown),Control::EventType::TOUCH_DOWN);
	settingsGameBtn->setTag(Btn_Music_TAG);
	addChild(settingsGameBtn);



	Scale9Sprite* btnNormal4 = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite* btnPress4 = Scale9Sprite::create(PRESS_MENU);
	LabelTTF* loadGameTTF = LabelTTF::create(LanguageString::getInstance()->getLanguageString(LOAD_GAME)->getCString(),FONT_MENU,Btn_FontSize);
	ControlButton* loadGameBtn = ControlButton::create(loadGameTTF,btnNormal4);
	loadGameBtn->setBackgroundSpriteForState(btnPress4, Control::State::SELECTED);

	loadGameBtn->setPosition(ccp(visibleSize.width/2,visibleSize.height-360));
	loadGameBtn->setPreferredSize(Size(Btn_Width,Btn_Height));
	loadGameBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(MenuScene::menuTouchDown),Control::EventType::TOUCH_DOWN);
	loadGameBtn->setTag(Btn_Load_Game_TAG);
	addChild(loadGameBtn);

	Scale9Sprite* btnNormal5 = Scale9Sprite::create(NORMAL_MENU);
	Scale9Sprite* btnPress5 = Scale9Sprite::create(PRESS_MENU);
	LabelTTF* quitGameTTF = LabelTTF::create(LanguageString::getInstance()->getLanguageString(QUIT_GAME)->getCString(),FONT_MENU,Btn_FontSize);
	ControlButton* quitGameBtn = ControlButton::create(quitGameTTF,btnNormal5);
	quitGameBtn->setBackgroundSpriteForState(btnPress5, Control::State::SELECTED);

	quitGameBtn->setPosition(ccp(visibleSize.width/2,visibleSize.height-420));
	quitGameBtn->setPreferredSize(Size(Btn_Width,Btn_Height));
	quitGameBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(MenuScene::menuTouchDown),Control::EventType::TOUCH_DOWN);
	quitGameBtn->setTag(Btn_Quit_Game_TAG);
	addChild(quitGameBtn);

}

void MenuScene:: menuTouchDown(Object* pSender,Control::EventType event)
{
	Util::playAudioEffect(BUTTON_CLICK,false);
	log("single touched");
	ControlButton* button = (ControlButton*)pSender;
	int tag = button->getTag();
	
	switch(tag)
	{
		case Btn_Single_Game_TAG:
			{
				log("single game");
				Director::getInstance()->pushScene(MapChooseScene::createScene());
			}

		case Btn_Multi_Game_TAG:
			{
				log("multi game");
				break;
			}

		case Btn_Music_TAG:
			{
				bool music_on = UserDefault::getInstance()->getBoolForKey(MUSIC_ON_KEY,true);

				if(music_on)
				{
					UserDefault::getInstance()->setBoolForKey(MUSIC_ON_KEY,false);
					button->setTitleForState(LanguageString::getInstance()->getLanguageString(MUSIC_OFF)->getCString(),Control::State::NORMAL);
				}else
				{
					UserDefault::getInstance()->setBoolForKey(MUSIC_ON_KEY,true);
					button->setTitleForState(LanguageString::getInstance()->getLanguageString(MUSIC_ON)->getCString(),Control::State::NORMAL);
				}
		
				break;
			}
		case Btn_Quit_Game_TAG:
			{
				log("quit game");
				popupLayer();
				break;
			}

		case Btn_Load_Game_TAG:
			{
				log("load game");
				popupLoadGameLayer();
				break;
			}
	   default:  
		   break;
	}

	
}

void MenuScene::popupLoadGameLayer()
{
  
    PopupLayer* popDialog = PopupLayer::create(DIALOG_BG);
   
	popDialog->setContentSize(CCSizeMake(Quit_Dialog_Size_Width, winSize.height)); 
    popDialog->setTitle(LanguageString::getInstance()->getLanguageString(LOAD_GAME)->getCString());
    popDialog->setContentText(LanguageString::getInstance()->getLanguageString(DIALOG_CONTENT)->getCString(), 20, 60, 250);
	popDialog->setPopType(LOADGAME);
    popDialog->setCallbackFunc(this, callfuncN_selector(MenuScene::quitButtonCallback));
   
    popDialog->addButton(BUTTON_BG2, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(CANCEL)->getCString(), Btn_Quit_Cancel_TAG);
  
    this->addChild(popDialog);
}



void MenuScene::popupLayer(){
    // 定义一个弹出层，传入一张背景图
    PopupLayer* popDialog = PopupLayer::create(DIALOG_BG);
    // ContentSize 是可选的设置，可以不设置，如果设置把它当作 9 图缩放
    popDialog->setContentSize(CCSizeMake(Quit_Dialog_Size_Width, Quit_Dialog_Size_Height)); 
    popDialog->setTitle(LanguageString::getInstance()->getLanguageString(DIALOG_TITLE)->getCString());
    popDialog->setContentText(LanguageString::getInstance()->getLanguageString(DIALOG_CONTENT)->getCString(), 20, 60, 250);
    // 设置回调函数，回调传回一个 CCNode 以获取 tag 判断点击的按钮
    // 这只是作为一种封装实现，如果使用 delegate 那就能够更灵活的控制参数了
    popDialog->setCallbackFunc(this, callfuncN_selector(MenuScene::quitButtonCallback));
    // 添加按钮，设置图片，文字，tag 信息
    popDialog->addButton(BUTTON_BG1, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(OK)->getCString(), Btn_Quit_OK_TAG);
    popDialog->addButton(BUTTON_BG2, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(CANCEL)->getCString(), Btn_Quit_Cancel_TAG);
    // 添加到当前层
    this->addChild(popDialog);
}

void MenuScene::quitButtonCallback(Node *pNode)	
{
	Util::playAudioEffect(BUTTON_CLICK,false);
	if(pNode->getTag() == Btn_Quit_OK_TAG)
	{
		Director::getInstance()->end();
	}else
	{
		pNode->getParent()->getParent()->removeFromParent();
	}
	
}
