#include "MapChooseScene.h"

USING_NS_CC;

Scene* MapChooseScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MapChooseScene::create();

	scene->addChild(layer);

	return scene;

}

bool MapChooseScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	
    currentPage = 1;
	addBackgroundSprite();

	addScrollView();


	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan=CC_CALLBACK_2(MapChooseScene::onTouchBegan,this);

	listener->onTouchMoved=CC_CALLBACK_2(MapChooseScene::onTouchMoved,this);
	listener->onTouchEnded=CC_CALLBACK_2(MapChooseScene::onTouchEnded,this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	
	Menu* menu = Menu::create();
	addChild(menu);

	MenuItem* backItem = MenuItemImage::create("images/back_normal.png", "images/back_pressed.png",
		this, menu_selector(MapChooseScene::back));
	menu->addChild(backItem);

	backItem->setPosition(ccp(winSize.width / 2 - backItem->getContentSize().width / 2,
		backItem->getContentSize().height / 2 - winSize.height / 2));

	return true;
}

void MapChooseScene::back(Object*)
{
	Director::getInstance()->popScene();
}

void MapChooseScene::addScrollView()
{
	Point center = ccp(visibleSize.width / 2, visibleSize.height / 2);

	_spritesContainer = Layer::create();

	Sprite* beachSprite = Sprite::create(BEACH_ITEM);
	Sprite* seaSprite = Sprite::create(SEA_ITEM);
	Sprite* snowSprite = Sprite::create(SNOW_ITEM);


	_spritesContainer->addChild(beachSprite);
	beachSprite->setPosition(ccpAdd(center, ccp(0, 0)));

	_spritesContainer->addChild(seaSprite);
	seaSprite->setPosition(ccpAdd(center, ccp(visibleSize.width, 0)));

	_spritesContainer->addChild(snowSprite);
	snowSprite->setPosition(ccpAdd(center, ccp(2 * visibleSize.width, 0)));


	_spritesContainer->setPosition(CCPointZero);
	_spritesContainer->setContentSize(CCSize(visibleSize.width * MAP_COUNT, visibleSize.height));

	scrollView = ScrollView::create();
	
	
	scrollView->setContainer(_spritesContainer);
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->setTouchEnabled(true);
	scrollView->setPosition(CCPointZero);
	
	scrollView->setViewSize(visibleSize);
	scrollView->setContentOffset(CCPointZero,true);
	scrollView->setContentSize(CCSize(visibleSize.width * MAP_COUNT, visibleSize.height));

	scrollView->setDelegate(this);

	scrollView->setBounceable(false);

	addChild(scrollView);
}

bool MapChooseScene::onTouchBegan(Touch * touch,Event *unused_event)

{
	beginTouchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
	log("touch begain");
	return true;

}

void MapChooseScene::onTouchMoved(Touch*touch,Event*unused_event)

{

	log("touch moved");

}

void MapChooseScene::onTouchEnded(Touch*touch,Event *unused_event)
{
	Util::playAudioEffect(BUTTON_CLICK,false);
	Point endPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
    float distance = endPoint.x - beginTouchPoint.x;
    if(fabs(distance) > TOUCH_DISTANCE)
    {
        adjustScrollView(distance);
    }else
	{
		if (currentPage == 1)
		{
			auto scene = TransitionFadeBL::create(1.5, BeachScene::createScene());

			Director::getInstance()->pushScene(scene);
		}
		if(currentPage == 2)
		{
			auto scene = 	TransitionFadeBL::create(1.5, SeaScene::createScene());
	
			Director::getInstance()->pushScene(scene);
		}
		if (currentPage == 3)
		{
			auto scene = TransitionFadeBL::create(1.5, SnowScene::createScene());

			Director::getInstance()->pushScene(scene);
		}
		
	}
}



void MapChooseScene::adjustScrollView(float offset)
{

    if (offset<0)
    {
        currentPage ++;
    }else
    {
        currentPage --;
    }
 
    if (currentPage <1)
    {
        currentPage = 1;
    }
 
    if(currentPage > MAP_COUNT)
    {
        currentPage = MAP_COUNT;
    }

        CCPoint  adjustPos = ccp(- visibleSize.width * (currentPage-1), 0);
        scrollView->setContentOffset(adjustPos, true);



}
void MapChooseScene::scrollViewDidScroll(ScrollView* view)
{
		
	//do something

}




void MapChooseScene::addBackgroundSprite()
{
	Sprite* state_bg= Sprite::create(STAGE_BACKGROUND);
	state_bg->setPosition(ccp(0,0));
	state_bg->setAnchorPoint(ccp(0,0));
	addChild(state_bg);
}

void MapChooseScene::scrollViewDidZoom(ScrollView* view)

{

	//do something

}

void MapChooseScene::scrollViewMoveOver(ScrollView* view)

{

	//do something

}