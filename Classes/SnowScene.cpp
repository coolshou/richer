#include "SnowScene.h"


Scene* SnowScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SnowScene::create();

	scene->addChild(layer);

	return scene;

}

bool SnowScene::init()
{
	addMap();
	initTiledGrid();
	initPropTiledID();
	if ( !GameBaseScene::init() )
	{
		return false;
	}

	return true;
}


void SnowScene::addMap()
{
	_map = TMXTiledMap::create( "map/snow.tmx");
	addChild(_map);
	
}

void SnowScene::initTiledGrid()
{
	tiledColsCount = 19;
	tiledRowsCount = 17;
	canPassGrid = new  bool*[tiledRowsCount];  
	 for(int i=0;i<tiledRowsCount;i++)
     canPassGrid[i]=new bool [tiledColsCount];	

	 

	for(int row = 0;row<tiledRowsCount;row++)
	{
		for(int col = 0;col<tiledColsCount;col++)
		{
			canPassGrid[row][col] = false;
		}
	}
	
	 
}

void SnowScene::initPropTiledID()
{
	 blank_land_tiledID   = 1;
	 strength_30_tiledID  = 4;
	 strength_50_tiledID  = 5;
	 strength_80_tiledID  = 6;

	 randomEvent_tiledID  = 7;
	 lottery_tiledID      = 8;
	 stock_tiledID        = 9;

	 player2_building_1_tiledID = 10;
	 player2_building_2_tiledID = 11;
	 player2_building_3_tiledID = 12;

	 player1_building_1_tiledID = 13;
	 player1_building_2_tiledID = 14;
	 player1_building_3_tiledID = 15;

	 map_level = 3;
	 saveJsonName = "snow_save.json";
	
}

