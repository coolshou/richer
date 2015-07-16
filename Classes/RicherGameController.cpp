#include "RicherGameController.h"
#include "GameBaseScene.h"
#include "RouteNavigation.h"
#include "Util.h"

RicherGameController* RicherGameController::richerGameController_Instance = NULL; 

bool RicherGameController::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

	callEndGoFunc = CallFunc::create(CC_CALLBACK_0(RicherGameController::endGo, this));
	registerNotificationObserver();
	
	oneRoundDone = false;
	
	
	positionAroundEnd;
	positionAroundEnd = new  float*[4];  
	for(int i=0;i<4;i++)
    positionAroundEnd[i]=new float [2];	
    return true;
}


void RicherGameController::registerNotificationObserver()
{
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(RicherGameController::receivedMsg),
		MSG_PICKONE_TOGO,
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(RicherGameController::receivedMsg),
		MSG_AROUND_LAND,
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(RicherGameController::receivedMsg),
		MSG_HANDLE_PROP_EVENT,
		NULL);
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(RicherGameController::receivedMsg),
		MSG_MOVE_ONE_STEP,
		NULL);
}

void RicherGameController::receivedMsg(Object* data)
{
	int retMsgType =((String*)data)->intValue();

	if(retMsgType == MSG_PICKONE_TOGO_TAG)
	{	
		pickOnePlayerToGo();
	}

	if(retMsgType == MSG_AROUND_LAND_TAG)
	{	
		aroundLandEvent();
	}
	if(retMsgType == MSG_HANDLE_PROP_EVENT_TAG)
	{	
		handlePropEvent();
	}
	if(retMsgType == MSG_MOVE_ONE_STEP_TAG)
	{	
		moveOneStep(_richerPlayer);
	}	
	
}

RicherGameController* RicherGameController::getInstance()
{
	if(!richerGameController_Instance)
	{  
		richerGameController_Instance = RicherGameController::create();  
    }  

	richerGameController_Instance->retain();
    return richerGameController_Instance;  

}

RicherGameController::~RicherGameController()
{
	for(int i = 0; i <4; i++)
	{
		delete[] positionAroundEnd[i];
	}
	delete[] positionAroundEnd;
	spawnAction->release();


}

void RicherGameController::moveOneStep(RicherPlayer* richerPlayer)
{
	Util::playAudioEffect(WALK_MP3,false);
	    nextRow = _rowVector[stepHasGone+1];
		nextCol = _colVector[stepHasGone+1];
		int distanceRow = nextRow - currentRow;
		int distanceCol = nextCol - currentCol;

		if(distanceRow >0)//up
		{
			moveBy = MoveBy::create(playerGoTotalTime,ccp(0,tiledHeight)); 
			repeate = Repeat::create(richerPlayer->getUp(),1);
		}
		if(distanceRow <0)//down
		{
			moveBy = MoveBy::create(playerGoTotalTime,ccp(0,-tiledHeight)); 
			repeate = Repeat::create(richerPlayer->getDown(),1);
		}
		if(distanceCol >0)//right
		{
			moveBy = MoveBy::create(playerGoTotalTime,ccp(tiledWidth,0)); 
			repeate = Repeat::create(richerPlayer->getRight(),1);
		}
		if(distanceCol <0)//left
		{
			moveBy = MoveBy::create(playerGoTotalTime,ccp(-tiledWidth,0)); 
			repeate = Repeat::create(richerPlayer->getLeft(),1);
		}
		
		spawnAction = Sequence::create(Spawn::create(moveBy,repeate,NULL),callEndGoFunc,NULL);
		spawnAction->retain();
		richerPlayer->runAction(spawnAction);
}

void RicherGameController::startRealGo(std::vector<int> rowVector,std::vector<int> colVector,RicherPlayer* richerPlayer)
{
	currentRow = rowVector[0];
	currentCol = colVector[0];
	nextRow =0;
	nextCol =0;

	_rowVector=rowVector;
	_colVector=colVector;
	_richerPlayer =richerPlayer;
	stepHasGone = 0;
	stepsCount = _rowVector.size()-1;
	moveOneStep(richerPlayer);


	
}

void RicherGameController::endGo()

{

	GameBaseScene::pathMarkVector.at(stepHasGone)->setVisible(false);

	stepHasGone++;

	if(stepHasGone >= stepsCount)
	{

		String * str = String::createWithFormat("%d-%f-%f-%d",MSG_BLOCK_WAY_EVENT_TAG,0.0f,0.0f,_richerPlayer->getTag());
		NotificationCenter::getInstance()->postNotification(MSG_BLOCK_WAY_EVENT,str);
		return;
	}

	currentRow = nextRow;
	currentCol = nextCol;
	Size titleSize = GameBaseScene::wayLayer->getLayerSize();
	int passId = GameBaseScene::wayLayer->getTileGIDAt(Point(currentCol,titleSize.height-currentRow-1));
	if(passId == GameBaseScene::lottery_tiledID)
	 {
		 String * str = String::createWithFormat("%d-%f-%f-%d-%d",MSG_LOTTERY_TAG,1.0f,1.0f,_richerPlayer->getTag(),MOVEPASS);
		 NotificationCenter::getInstance()->postNotification(MSG_LOTTERY,str);
		 return;
	 }

	 if(passId == GameBaseScene::stock_tiledID)
	 {
		 String * str = String::createWithFormat("%d-%f-%f-%d-%d",MSG_STOCK_TAG,1.0f,1.0f,_richerPlayer->getTag(),MOVEPASS);
		 NotificationCenter::getInstance()->postNotification(MSG_STOCK,str);
		 return;
	 }

	moveOneStep(_richerPlayer);

	//Point pointInMap = Util::GL2map(Vec2(currentRow,currentCol), GameBaseScene::_map);


	log("go end");
	
}

void RicherGameController::pickOnePlayerToGo()
{
	for(auto it=GameBaseScene::players_vector.begin();it!=GameBaseScene::players_vector.end();it++)
	{
		RicherPlayer* richerPlayer = dynamic_cast<RicherPlayer*>(*it);
		if(richerPlayer->getMoney() <= 0)
		{
			String * str = String::createWithFormat("%d-%f-%f-%d",MSG_GAME_OVER_TAG,0.0f,0.0f,richerPlayer->getTag());
			NotificationCenter::getInstance()->postNotification(MSG_GAME_OVER,str);
			return;
		}

	}


	for(auto it=GameBaseScene::players_vector.begin();it!=GameBaseScene::players_vector.end();it++)
		{
			RicherPlayer* richerPlayer = dynamic_cast<RicherPlayer*>(*it);

			if(richerPlayer->getIsMyTurn() && richerPlayer->restTimes > 0 )
			{
				String * str = String::createWithFormat("%d-%f-%f-%d",MSG_REST_TAG,0.0f,0.0f,richerPlayer->getTag());
				NotificationCenter::getInstance()->postNotification(MSG_REST,str);
				return;
			}

			if(richerPlayer->getIsMyTurn() && richerPlayer->restTimes == 0)
			{
				richerPlayer->setVisible(true);

				if(richerPlayer->getTag() == PLAYER_1_TAG )
				{
					NotificationCenter::getInstance()->postNotification(MSG_GO,String::createWithFormat("%d",MSG_GO_SHOW_TAG));
					return;
				}

				if(richerPlayer->stop_x > 0)
				{

					int gid = GameBaseScene::landLayer->getTileGIDAt(ccp(richerPlayer->stop_x,richerPlayer->stop_y));

					if(gid != GameBaseScene::blank_land_tiledID && gid != GameBaseScene::player2_building_1_tiledID && gid != GameBaseScene::player2_building_2_tiledID && gid != GameBaseScene::player2_building_3_tiledID)
					{
						int playerStrength = richerPlayer->getStrength();
						int randomSkill_index = rand()%3;
						int needLostStrength = 0;
						int landLevel = 0;
						if(gid == GameBaseScene::player1_building_1_tiledID)
						{
							landLevel =  GameBaseScene::player2_building_1_tiledID;
						}
						if(gid == GameBaseScene::player1_building_2_tiledID)
						{
							landLevel =  GameBaseScene::player2_building_2_tiledID;
						}
						if(gid == GameBaseScene::player1_building_3_tiledID)
						{
							landLevel =  GameBaseScene::player2_building_3_tiledID;
						}

						switch(randomSkill_index)
						{
						case 0:
							{
								needLostStrength = 80-richerPlayer->skill_vector.at(0)*10;
								break;
							}
						case 1:
							{
							
							}
						case 2:
							{
								needLostStrength = 110-richerPlayer->skill_vector.at(2)*10;
								break;
							}
						}

						if(playerStrength >= needLostStrength)
						{
							String * str = String::createWithFormat("%d-%f-%f-%d-%d-%d-%d",MSG_USE_SKILL_TAG,richerPlayer->stop_x ,richerPlayer->stop_y,richerPlayer->getTag(),randomSkill_index,needLostStrength,landLevel);
							NotificationCenter::getInstance()->postNotification(MSG_USE_SKILL,str);
							return;
						}

					}

				}
				

				
				

				int randNumber = rand()%6 + 1; 
				RouteNavigation::getInstance()->getPath(richerPlayer,randNumber,GameBaseScene::canPassGrid,GameBaseScene::tiledRowsCount,GameBaseScene::tiledColsCount);
				richerPlayer->startGo(RouteNavigation::getInstance()->getPathRow_vector(),RouteNavigation::getInstance()->getPathCols_vector());
				return;
			}

		}
	oneRoundDone = true;
	resetPlayerGoTurn();
	
}

void RicherGameController::resetPlayerGoTurn()
{
	for(auto it=GameBaseScene::players_vector.begin();it!=GameBaseScene::players_vector.end();it++)
	{
		RicherPlayer* richerPlayer = dynamic_cast<RicherPlayer*>(*it);
		richerPlayer->setIsMyTurn(true);

		richerPlayer->restTimes--;
		if(richerPlayer->restTimes < 0)
		{
			richerPlayer->restTimes = 0;
		}

	}
	NotificationCenter::getInstance()->postNotification(MSG_ROUND_COUNT,String::createWithFormat("%d",MSG_ROUND_COUNT_TAG));
	pickOnePlayerToGo();
}


void RicherGameController::handlePropEvent()
{
	oneRoundDone =false;
	float playerEnd_X = _colVector[stepsCount]*32;
    float playerEnd_Y = _rowVector[stepsCount]*32 + 32;

	 Point pointInMap = Util::GL2map(Vec2(playerEnd_X,playerEnd_Y), GameBaseScene::_map);
	// _richerPlayer->stop_x = pointInMap.x;
	// _richerPlayer->stop_x = pointInMap.y;
	 int endId = GameBaseScene::wayLayer->getTileGIDAt(pointInMap);
	 if(endId == GameBaseScene::randomEvent_tiledID)
	 {
		 String * str = String::createWithFormat("%d-%f-%f-%d",MSG_RANDOM_ASK_EVENT_TAG,pointInMap.x,pointInMap.y,_richerPlayer->getTag());
		 NotificationCenter::getInstance()->postNotification(MSG_RANDOM_ASK_EVENT,str);
		 return;
	 }
	 if(endId == GameBaseScene::strength_30_tiledID)
	 {
		 String * str = String::createWithFormat("%d-%f-%f-%d",MSG_STRENGTH_UP30_TAG,pointInMap.x,pointInMap.y,_richerPlayer->getTag());
		 NotificationCenter::getInstance()->postNotification(MSG_STRENGTH_UP,str);
		 return;
	 }

	 if(endId == GameBaseScene::strength_50_tiledID)
	 {
		 String * str = String::createWithFormat("%d-%f-%f-%d",MSG_STRENGTH_UP50_TAG,pointInMap.x,pointInMap.y,_richerPlayer->getTag());
		 NotificationCenter::getInstance()->postNotification(MSG_STRENGTH_UP,str);
		 return;
	 }

	 if(endId == GameBaseScene::strength_80_tiledID)
	 {
		 String * str = String::createWithFormat("%d-%f-%f-%d",MSG_STRENGTH_UP80_TAG,pointInMap.x,pointInMap.y,_richerPlayer->getTag());
		 NotificationCenter::getInstance()->postNotification(MSG_STRENGTH_UP,str);
		 return;
	 }
	 
	 if(endId == GameBaseScene::lottery_tiledID)
	 {
		 String * str = String::createWithFormat("%d-%f-%f-%d-%d",MSG_LOTTERY_TAG,pointInMap.x,pointInMap.y,_richerPlayer->getTag(),GOEND);
		 NotificationCenter::getInstance()->postNotification(MSG_LOTTERY,str);
		 return;
	 }

	 if(endId == GameBaseScene::stock_tiledID)
	 {
		 String * str = String::createWithFormat("%d-%f-%f-%d-%d",MSG_STOCK_TAG,pointInMap.x,pointInMap.y,_richerPlayer->getTag(),GOEND);
		 NotificationCenter::getInstance()->postNotification(MSG_STOCK,str);
		 return;
	 }
	 
	 aroundLandEvent();
}


void RicherGameController::aroundLandEvent()
{
	float playerEnd_X = _colVector[stepsCount]*32;
    float playerEnd_Y = _rowVector[stepsCount]*32 + 32;
    // up
	positionAroundEnd[0][0] = playerEnd_X;
	positionAroundEnd[0][1] = playerEnd_Y + 32;

    // down
    positionAroundEnd[1][0] = playerEnd_X;
    positionAroundEnd[1][1] = playerEnd_Y - 32;

    // left
	positionAroundEnd[2][0] = playerEnd_X - 32;
    positionAroundEnd[2][1] = playerEnd_Y;
   
    // right
	positionAroundEnd[3][0] = playerEnd_X + 32;
    positionAroundEnd[3][1] = playerEnd_Y;

	 log("handlePropEvent() called");
	 
	for (int i = 0; i < 4; i++) 
	 {
		 Point ptMap = Util::GL2map(Vec2(positionAroundEnd[i][0],positionAroundEnd[i][1]), GameBaseScene::_map);
		 const int titleId = GameBaseScene::landLayer->getTileGIDAt(ptMap);

		 float x = ptMap.x;
		 float y = ptMap.y;
		 _richerPlayer->stop_x = x;
		 _richerPlayer->stop_y = y;
		 if(titleId == GameBaseScene::blank_land_tiledID)
			{
					//send a message to show buy dialog

					String * str = String::createWithFormat("%d-%f-%f-%d",MSG_BUY_BLANK_TAG,x,y,_richerPlayer->getTag());
					 
					// NotificationCenter::getInstance()->postNotification(MSG_BUY,String::createWithFormat("%d",MSG_BUY_BLANK_TAG));
					NotificationCenter::getInstance()->postNotification(MSG_BUY,str);
					break;
			}
		 if(titleId == GameBaseScene::player1_building_1_tiledID)
			{
					if(_richerPlayer->getTag() == PLAYER_1_TAG)
					{
						 String * str = String::createWithFormat("%d-%f-%f-%d",MSG_BUY_LAND_1_TAG,x,y,_richerPlayer->getTag());
						 NotificationCenter::getInstance()->postNotification(MSG_BUY,str);			
					}else
					{
						String * str = String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_1_TAG,x,y,_richerPlayer->getTag());
						NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);	
					}
					
					break;
			}
		 if(titleId == GameBaseScene::player1_building_2_tiledID)
			{
					if(_richerPlayer->getTag() == PLAYER_1_TAG)
					{
						 String * str = String::createWithFormat("%d-%f-%f-%d",MSG_BUY_LAND_2_TAG,x,y,_richerPlayer->getTag());
						 NotificationCenter::getInstance()->postNotification(MSG_BUY,str);			
					}else
					{
						String * str = String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_2_TAG,x,y,_richerPlayer->getTag());
						NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);	
					}
					break;
			}	

		 if(titleId == GameBaseScene::player1_building_3_tiledID)
			{
					if(_richerPlayer->getTag() != PLAYER_1_TAG)
					{
						String * str = String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_3_TAG,x,y,_richerPlayer->getTag());
						NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);	
					}else
					{
						NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));
					}
					break;
			}

		 if(titleId == GameBaseScene::player2_building_1_tiledID)
			{
					if(_richerPlayer->getTag() == PLAYER_2_TAG)
					{
						String * str = String::createWithFormat("%d-%f-%f-%d",MSG_BUY_LAND_1_TAG,x,y,_richerPlayer->getTag());				
						NotificationCenter::getInstance()->postNotification(MSG_BUY,str);			
					}else
					{
						String * str = String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_1_TAG,x,y,_richerPlayer->getTag());
						NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);	
					}
					break;
			}
		 if(titleId == GameBaseScene::player2_building_2_tiledID)
			{
					if(_richerPlayer->getTag() == PLAYER_2_TAG)
					{
						String * str = String::createWithFormat("%d-%f-%f-%d",MSG_BUY_LAND_2_TAG,x,y,_richerPlayer->getTag());				
						NotificationCenter::getInstance()->postNotification(MSG_BUY,str);			
					}else
					{
						String * str = String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_2_TAG,x,y,_richerPlayer->getTag());
						NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);	
					}
					break;
			}
		 if(titleId == GameBaseScene::player2_building_3_tiledID)
			{
					if(_richerPlayer->getTag() != PLAYER_2_TAG)
					{
						String * str = String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_3_TAG,x,y,_richerPlayer->getTag());
						NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);			
					}else
					{
						NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));
					}
					break;
			}
		 
	 }

}

