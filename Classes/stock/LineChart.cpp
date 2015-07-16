#include "GameBaseScene.h"
#include "LineChart.h"


LineChart::LineChart()
{

}

LineChart::~LineChart()
{

}

bool LineChart::initChart(RicherPlayer* player,vector<float> stock_pointvec1,vector<float> stock_pointvec2,vector<float> stock_pointvec3,vector<float> stock_pointvec4,vector<float> stock_pointvec5)
{
   
    
    if ( !LayerColor::initWithColor(Color4B(0,0,0,255))) 
	{
		 return false; 
	}

	this->stock_pointvec1 = stock_pointvec1;
	this->stock_pointvec2 = stock_pointvec2;
	this->stock_pointvec3 = stock_pointvec3;
	this->stock_pointvec4 = stock_pointvec4;
	this->stock_pointvec5 = stock_pointvec5;

	richerPlayer = player;
	playerStockMap = player->stockMap;
	initStockVector(playerStockMap);
	drawNode = DrawNode::create();
	this->addChild(drawNode);

	tv = TableView::create(this, Size(650, 160));
    tv->setAnchorPoint(Point(0, 0));
    tv->setPosition(10, VisibleRect::getVisibleRect().size.height * 1 /2);
	
    tv->setDelegate(this);
    addChild(tv);
	initMenu();
	

	
	selectedTag =0;  

	float tableY =  VisibleRect::getVisibleRect().size.height * 1/2;
	arrowSprite_left->setPosition(600+arrowSprite_left->getContentSize().width,tableY +selectedTag*32);
	arrowSprite_right->setPosition(10,tableY + selectedTag*32);

	log("all cellY is %f",tableY);
	setData(getsock_pointVec(selectedTag));
	drawpic();



    return true;
}




LineChart* LineChart::createChart(RicherPlayer* player,vector<float> stock_pointvec1,vector<float> stock_pointvec2,vector<float> stock_pointvec3,vector<float> stock_pointvec4,vector<float> stock_pointvec5)
{
	LineChart* mLineChart = new LineChart();
	mLineChart->initChart(player,stock_pointvec1,stock_pointvec2,stock_pointvec3,stock_pointvec4,stock_pointvec5);
	mLineChart->autorelease();
	return mLineChart;
}


void LineChart::initMenu()
{
	Menu* menu = Menu::create();
	menu->setPosition(CCPointZero);
    setMenu(menu);
    MenuItemImage* buyMenuItemButton = MenuItemImage::create("images/buy_normal.png", "images/buy_pressed.png", this, menu_selector(LineChart::buttonCallback));
 
    buyMenuItemButton->setPosition(ccp(700,VisibleRect::getVisibleRect().size.height-110));
	buyMenuItemButton->setAnchorPoint(ccp(0,0));
	buyMenuItemButton->setTag(buy_button);
	menu->addChild(buyMenuItemButton);


	MenuItemImage* sellMenuItemButton = MenuItemImage::create("images/sell_normal.png", "images/sell_pressed.png", this, menu_selector(LineChart::buttonCallback));
 
    sellMenuItemButton->setPosition(ccp(700,VisibleRect::getVisibleRect().size.height-180));
	sellMenuItemButton->setAnchorPoint(ccp(0,0));
	sellMenuItemButton->setTag(sell_button);
	menu->addChild(sellMenuItemButton);


	MenuItemImage* backMenuItemButton = MenuItemImage::create("images/back_normal.png", "images/back_pressed.png", this, menu_selector(LineChart::buttonCallback));
 
    backMenuItemButton->setPosition(ccp(700,VisibleRect::getVisibleRect().size.height-250));
	backMenuItemButton->setAnchorPoint(ccp(0,0));
	backMenuItemButton->setTag(back_button);
	menu->addChild(backMenuItemButton);

	addChild(menu);


	arrowSprite_left = Sprite::create("images/arrow_left.png");
	arrowSprite_left->setPosition(ccp(-500,-500));
	arrowSprite_left->setAnchorPoint(ccp(0,0));
	addChild(arrowSprite_left);

	arrowSprite_right = Sprite::create("images/arrow_right.png");
	arrowSprite_right->setPosition(ccp(-500,-500));
	arrowSprite_right->setAnchorPoint(ccp(0,0));
	addChild(arrowSprite_right);
}

void LineChart::initStockVector(Map<int,Stock*> stockMap)
{
	
	stockVector.clear();
	float percent = 0;
	if(stock_pointvec1.size()>1)
	{
		percent = (stock_pointvec1.at(stock_pointvec1.size()-1) - stock_pointvec1.at(stock_pointvec1.size()-2))/stock_pointvec1.at(stock_pointvec1.size()-2)*100;
	}

	stockVector.pushBack(Stock::create(800100,LanguageString::getInstance()->getLanguageString(RICH_TECHNOLOGY),stock_pointvec1.at(stock_pointvec1.size()-1),stockMap.at(0)->getMakedealprice(),percent,stockMap.at(0)->getStoreNumber()));
	
	percent = 0;
	if(stock_pointvec2.size()>1)
	{
		percent = (stock_pointvec2.at(stock_pointvec2.size()-1) - stock_pointvec2.at(stock_pointvec2.size()-2))/stock_pointvec2.at(stock_pointvec2.size()-2)*100;
	}

	stockVector.pushBack(Stock::create(800200,LanguageString::getInstance()->getLanguageString(RICH_OIL),stock_pointvec2.at(stock_pointvec1.size()-1),stockMap.at(1)->getMakedealprice(),percent,stockMap.at(1)->getStoreNumber()));

	percent = 0;
	if(stock_pointvec3.size()>1)
	{
		percent = (stock_pointvec3.at(stock_pointvec3.size()-1) - stock_pointvec3.at(stock_pointvec3.size()-2))/stock_pointvec3.at(stock_pointvec3.size()-2)*100;
	}
	stockVector.pushBack(Stock::create(800300,LanguageString::getInstance()->getLanguageString(ICBC),stock_pointvec3.at(stock_pointvec1.size()-1),stockMap.at(2)->getMakedealprice(),percent,stockMap.at(2)->getStoreNumber()));

	percent = 0;
	if(stock_pointvec4.size()>1)
	{
		percent = (stock_pointvec4.at(stock_pointvec4.size()-1) - stock_pointvec4.at(stock_pointvec4.size()-2))/stock_pointvec4.at(stock_pointvec4.size()-2)*100;
	}
	stockVector.pushBack(Stock::create(800400,LanguageString::getInstance()->getLanguageString(HUATUO_MEDICINE),stock_pointvec4.at(stock_pointvec1.size()-1),stockMap.at(3)->getMakedealprice(),percent,stockMap.at(3)->getStoreNumber()));
	
	percent = 0;
	if(stock_pointvec5.size()>1)
	{
		percent = (stock_pointvec5.at(stock_pointvec5.size()-1) - stock_pointvec5.at(stock_pointvec5.size()-2))/stock_pointvec5.at(stock_pointvec5.size()-2)*100;
	}
	stockVector.pushBack(Stock::create(800500,LanguageString::getInstance()->getLanguageString(DEMOLITION_CONSTRUCTION),stock_pointvec5.at(stock_pointvec1.size()-1),stockMap.at(4)->getMakedealprice(),percent,stockMap.at(4)->getStoreNumber()));

	
	Label* code = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(STOCK_CODE)->getCString(),"", 20);
	code->setPosition(Point(20, 410 ));
	code->setAnchorPoint(ccp(0,0));
	addChild(code);

	Label* name = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(STOCK_NAME)->getCString(),"", 20);
	name->setPosition(Point(stockCellWidth+20, 410 ));
	name->setAnchorPoint(ccp(0,0));
	addChild(name);

	Label* nowprice = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(STOCK_NOWPRICE)->getCString(),"", 20);
	nowprice->setPosition(Point(stockCellWidth*2+20, 410 ));
	nowprice->setAnchorPoint(ccp(0,0));
	addChild(nowprice);

	Label* dealprice = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(STOCK_DEALPRICE)->getCString(),"", 20);
	dealprice->setPosition(Point(stockCellWidth*3+20, 410 ));
	dealprice->setAnchorPoint(ccp(0,0));
	addChild(dealprice);

	Label* percentLabel = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(STOCK_PERCENT)->getCString(),"", 20);
	percentLabel->setPosition(Point(stockCellWidth*4+20, 410 ));
	percentLabel->setAnchorPoint(ccp(0,0));
	addChild(percentLabel);


	Label* store = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(STOCK_STORE)->getCString(),"", 20);
	store->setPosition(Point(540, 410 ));
	store->setAnchorPoint(ccp(0,0));
	addChild(store);


	playerMoneyLabel = Label::createWithSystemFont(
		String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(PLAYER_MONEY)->getCString(),richerPlayer->getMoney())->getCString(),
		"", 20);
	playerMoneyLabel->setPosition(Point(20, 450 ));
	playerMoneyLabel->setAnchorPoint(ccp(0,0));
	addChild(playerMoneyLabel);

}

 void LineChart::buttonCallback(CCObject* pSender)
 {
	 int tag  = ((Node*)pSender)->getTag();
	 switch(tag)
	 {
	 case buy_button:
		 {
			 int diffMoney = richerPlayer->getMoney()-stockVector.at(selectedTag)->getNowPrice()*100;
			 if(diffMoney >= 0)
			 {
				Stock* s= playerStockMap.at(selectedTag);
				int storeNumber = s->getStoreNumber()+100;

				int dealPrice = (s->getMakedealprice()*s->getStoreNumber()+stockVector.at(selectedTag)->getNowPrice()*100)/(100+s->getStoreNumber());


				s->setStoreNumber(s->getStoreNumber()+100);
				s->setMakedealprice(dealPrice);
			

				stockVector.at(selectedTag)->setStoreNumber(storeNumber);
				Vector<Node*> cellCardVector = tv->cellAtIndex(selectedTag)->getChildren();
				StockCellCard* sdStore = (StockCellCard*)cellCardVector.at(cellCardVector.size()-1);
				sdStore->labelInfo->setString(String::createWithFormat("%d",storeNumber)->getCString());

				StockCellCard* sdDealPrice = (StockCellCard*)cellCardVector.at(cellCardVector.size()-3);
				sdDealPrice->labelInfo->setString(String::createWithFormat("%d",dealPrice)->getCString());


				richerPlayer->setMoney(diffMoney);

				playerMoneyLabel->setString(String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(PLAYER_MONEY)->getCString(),richerPlayer->getMoney())->getCString());


			 }else
			 {
				 CocosToast::createToast(this, String::createWithFormat("%s",LanguageString::getInstance()->getLanguageString(NO_MONEY_BUY_STOCK)->getCString())->getCString(), TOAST_SHOW_TIME,
					VisibleRect::getVisibleRect().size/2,NULL);
			 }



			 break;
		 }
	 case sell_button:
		 {
			 Stock* s= playerStockMap.at(selectedTag);
			int storeNumber = s->getStoreNumber();
			if(storeNumber > 0)
			{
				Vector<Node*> cellCardVector = tv->cellAtIndex(selectedTag)->getChildren();
				StockCellCard* sdStore = (StockCellCard*)cellCardVector.at(cellCardVector.size()-1);
				sdStore->labelInfo->setString(String::createWithFormat("%d",0)->getCString());

				StockCellCard* sdDealPrice = (StockCellCard*)cellCardVector.at(cellCardVector.size()-3);
				sdDealPrice->labelInfo->setString(String::createWithFormat("%d",0)->getCString());


				richerPlayer->setMoney(richerPlayer->getMoney() + storeNumber * stockVector.at(selectedTag)->getNowPrice());
				s->setMakedealprice(0);
				s->setStoreNumber(0);

				playerMoneyLabel->setString(String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(PLAYER_MONEY)->getCString(),richerPlayer->getMoney())->getCString());

			}
			 break;
		 }
	 case back_button:
		 {
			if(moveTag == GOEND)
			{
				NotificationCenter::getInstance()->postNotification(MSG_AROUND_LAND,String::createWithFormat("%d",MSG_AROUND_LAND_TAG));

			}else if(moveTag ==  MOVEPASS)
			{
				NotificationCenter::getInstance()->postNotification(MSG_MOVE_ONE_STEP,String::createWithFormat("%d",MSG_MOVE_ONE_STEP_TAG));
			}	
			this->removeFromParent();
			NotificationCenter::getInstance()->postNotification(MSG_STOCK_LAYER_DISMISS,String::createWithFormat("%d",MSG_STOCK_LAYER_DISMISS_TAG));
			 break;
		 }
	 }


 }

 void LineChart::sendMSGDealAroundLand()
{
	NotificationCenter::getInstance()->postNotification(MSG_AROUND_LAND,String::createWithFormat("%d",MSG_AROUND_LAND_TAG));
}
 void LineChart::sendMSGMoveOneStep()
{
	NotificationCenter::getInstance()->postNotification(MSG_MOVE_ONE_STEP,String::createWithFormat("%d",MSG_MOVE_ONE_STEP_TAG));
}
Size LineChart::cellSizeForTable(cocos2d::extension::TableView *table)
{
    return Size(100, 32);
}
void LineChart::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    
	for(int i=0;i<30;i++)
	{
		this->removeChildByTag(100+i);
	}

	int tag = cell->getTag();
	selectedTag =tag;
    log("******click id = %d",tag);
	float height = VisibleRect::getVisibleRect().size.height;
	float tableY =  VisibleRect::getVisibleRect().size.height * 1/2;
	arrowSprite_left->setPosition(600+arrowSprite_left->getContentSize().width,tableY +tag*32);
	arrowSprite_right->setPosition(10,tableY + tag*32);
	log("all height is %f",height);
	log("all cellY is %f",tableY);
	setData(getsock_pointVec(tag));
	drawpic();
	    
}

 vector<float> LineChart::getsock_pointVec(int id)
{
	switch(id)
	{
	case 0:
		{
			return stock_pointvec1;
			break;
		}
		
	case 1:
		{
			return stock_pointvec2;
			break;
		}
	case 2:
		{
			return stock_pointvec3;
			break;
		}
	case 3:
		{
			return stock_pointvec4;
			break;
		}
	case 4:
		{
			return stock_pointvec5;
			break;
		}

	}
	return  stock_pointvec1;
}

TableViewCell* LineChart::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();  
    LabelTTF *label;

    int colorTag = 0;
	if(stockVector.at(idx)->getPercent()>0)
	{
		colorTag = 1;
	}else
	{
		colorTag = -1;
	}

    if (cell==NULL) 
	{		
        cell = TableViewCell::create();
		cell->setTag(idx);  
		for(int i=0; i<6; i++)    
		{  
			switch(i)
			{
			case 0:
				{
					StockCellCard* card = StockCellCard::createCardSprite(String::createWithFormat("%d",stockVector.at(idx)->getCode()), stockCellWidth, stockCellHeight, stockCellWidth*i+10, 0,colorTag);    
					cell->addChild(card);
					break;
				}
			case 1:
				{
					StockCellCard* card = StockCellCard::createCardSprite(stockVector.at(idx)->getStockName(), stockCellWidth, stockCellHeight, stockCellWidth*i+10, 0,colorTag);    
					cell->addChild(card);
					break;
				}
			case 2:
				{
					StockCellCard* card = StockCellCard::createCardSprite(String::createWithFormat("%d",stockVector.at(idx)->getNowPrice()), stockCellWidth, stockCellHeight, stockCellWidth*i+10, 0,colorTag);    
					cell->addChild(card);
					break;
				}

			case 3:
				{
					StockCellCard* card = StockCellCard::createCardSprite(String::createWithFormat("%d",stockVector.at(idx)->getMakedealprice()), stockCellWidth, stockCellHeight, stockCellWidth*i+10, 0,colorTag);    
					cell->addChild(card);
					break;
				}
			case 4:
				{
					
					StockCellCard* card = StockCellCard::createCardSprite(String::createWithFormat("%.0f %s",stockVector.at(idx)->getPercent(),"%"), stockCellWidth, stockCellHeight, stockCellWidth*i+10, 0,colorTag);    
					cell->addChild(card);
					break;
				}
			case 5:
				{
					
					StockCellCard* card = StockCellCard::createCardSprite(String::createWithFormat("%d",stockVector.at(idx)->getStoreNumber()), stockCellWidth, stockCellHeight, stockCellWidth*i+10, 0,colorTag);    
					cell->addChild(card);
					break;
				}
			}
			

		} 

    }else{
        label = (LabelTTF*)cell->getChildByTag(2);
    }
    
    return cell;
}



ssize_t LineChart::numberOfCellsInTableView(cocos2d::extension::TableView *table){
    return 5;
}


void LineChart::drawpic()
{
	drawNode->clear();
	int maxValue = getMaxValue(pointvec);
	int maxValue2 = int((maxValue+100) / 100)* 100 ;
     maxValue1 = maxValue2  / 10;
    
    
     spaceRatio = 0.08f;  //y轴间距系数
     leftRatioX = 0.1f;   //x轴左侧间距系数
    
    
    int fontSize = 20;
    string fontName = StringUtils::format("Thonburi");
    
    Size layerSize = Size(VisibleRect::getVisibleRect().size.width, VisibleRect::getVisibleRect().size.height * 1 /2);
    
    
      layerHeight1 = 30;
    float layerHeight = layerHeight1;
    float layerWidth = layerSize.width;
    int count = layerSize.width /50;   
    for (int i = 0; i < 11; i++) {
        Point bPoint = Point(layerWidth* leftRatioX, layerHeight );
        Point ePoint = Point(layerWidth* leftRatioX+(count-2) * 50, layerHeight );
        Label* label = Label::createWithSystemFont(StringUtils::format("%d",maxValue1* i).c_str(), fontName.c_str(), fontSize);       
        label->setPosition(Point(layerWidth* 0.05f, layerHeight ));
		label->setTag(100+i);
        addChild(label);      
		drawNode->drawSegment(bPoint, ePoint, 0.5,Color4F(100, 100, 200, 200));		
        layerHeight += layerSize.height * spaceRatio;         
    }


	float layer_wd = layerSize.width * leftRatioX;
    for (int i = 0; i < count; i++) {
     

		Point bPoint  = Point(layer_wd, layerHeight1);        
		Point ePoint  = Point(layer_wd, layerSize.height * spaceRatio*10+layerHeight1); 
		if(i%2 == 0)
		{
			drawNode->drawSegment(bPoint,ePoint,0.5,Color4F(100, 100, 200, 200));
		}

		auto labelX = Label::createWithSystemFont(StringUtils::format("%d",i).c_str(), "Thonburi", 20);
        labelX->setPosition(Point(ePoint.x, 0));
		labelX->setAnchorPoint(ccp(0,0));
		labelX->setTag(100+11+i);
        this->addChild(labelX);
        layer_wd += 50;
     
    }
	

	drawLine(pointvec, Color4B(0, 255, 255, 255),Color4B(255, 0, 255, 255));
}


void LineChart::drawLine(vector<Point> vec,Color4B lineColor,Color4B dotColor)
{
	
    Size layerSize = Size(VisibleRect::getVisibleRect().size.width, VisibleRect::getVisibleRect().size.height * 1 /2);
       
    float layerWidth = layerSize.width;
        
    float tempWidth = layerSize.height * spaceRatio;
    float tempWidth2 = 0;
    
    float tempHeight1 = maxValue1  ;   

    double  ratio = tempWidth/tempHeight1;
    
    
    /**********************开始画线**********************/
    std::vector<Point>::iterator beforePoint;
    std::vector<Point>::iterator currentPoint;
    
    beforePoint = vec.begin();
    
    for (currentPoint = vec.begin() + 1;currentPoint != vec.end() ; currentPoint++) {
        Point bPoint  = *beforePoint;
        bPoint = Point(bPoint.x + layerWidth* leftRatioX, bPoint.y * ratio + layerHeight1 +tempWidth2);
        
        Point ePoint  = *currentPoint;
        ePoint = Point(ePoint.x + layerWidth* leftRatioX, ePoint.y * ratio + layerHeight1 +tempWidth2);
        
		drawNode->drawSegment(bPoint, ePoint, 0.8,Color4F::RED);
        beforePoint = currentPoint;
        
    }

     /**********************结束画线**********************/   
   
    /********************开始画点**********************************************/
    beforePoint = vec.begin();
    DrawPrimitives::setDrawColor4B(dotColor.r, dotColor.g, dotColor.b, dotColor.a);
    Point bPoint  = *beforePoint;
    bPoint = Point(bPoint.x +layerWidth* leftRatioX, bPoint.y * ratio + layerHeight1 +tempWidth2);

	drawNode->drawDot(bPoint, 5, Color4F::YELLOW); 

    int i = 2;
    for (currentPoint = vec.begin() + 1;currentPoint != vec.end() ; currentPoint++) {
        Point ePoint  = *currentPoint;    
        ePoint = Point(ePoint.x + layerWidth* leftRatioX, ePoint.y * ratio + layerHeight1 + tempWidth2);              
        drawNode->drawDot(ePoint, 5, Color4F::YELLOW); 
        i++;
    }
     /********************结束画点*********************************************END**/
    
}



void LineChart::setData(vector<float> data)
{
	pointvec.clear();
    vector<float>::iterator it;
    int i = 0;
    
    for (it = data.begin();it != data.end();it++) {
        float f = *it;
        pointvec.push_back(Point(50 * (i+1), f));               
        i++;
        
    }
    
}

double LineChart::getMaxValue(std::vector<Point> vec)
{
    
    double maxY =1;
    
    for (int i = 0; i < vec.size(); i++)
	{
        float num = vec.at(i).y;
        if (maxY < abs(num)) 
		{
            maxY = abs(num);
        }
    }
    return maxY;
}

