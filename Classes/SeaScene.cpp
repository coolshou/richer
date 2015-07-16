#include "SeaScene.h"


Scene* SeaScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SeaScene::create();

	scene->addChild(layer);

	return scene;

}

bool SeaScene::init()
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


void SeaScene::addMap()
{
	_map = TMXTiledMap::create( "map/sea.tmx");
	addChild(_map);
	
}

void SeaScene::initTiledGrid()
{
	tiledColsCount = 20;
	tiledRowsCount = 15;
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
	log("");
	 
}

void SeaScene::initPropTiledID()
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

	 map_level = 2;
	 saveJsonName = "sea_save.json";
	
}

