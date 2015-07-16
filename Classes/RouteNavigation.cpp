#include "RouteNavigation.h"
#include "GameBaseScene.h"

RouteNavigation* RouteNavigation::routeNav_Instance = NULL; 

RouteNavigation::RouteNavigation(void)
{
		struct timeval now; 
		gettimeofday(&now, NULL);
		unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);    //都转化为毫秒 
		srand(rand_seed);
}


RouteNavigation::~RouteNavigation(void)
{
	routeNav_Instance = NULL; 

	pathCols_vector.clear();
	pathRow_vector.clear();
	std::vector<int>(pathCols_vector).swap(pathCols_vector);
	std::vector<int>(pathRow_vector).swap(pathRow_vector);
}

RouteNavigation* RouteNavigation::getInstance()
{
	if(!routeNav_Instance)
	{  
        routeNav_Instance = new RouteNavigation();  
    }  
    return routeNav_Instance;  

}

void RouteNavigation::getPath(RicherPlayer* player,int stepsCount,bool** canPassGrid,int gridRowsCount,int gridColsCount)
{
	
	pathCols_vector.clear();
	pathRow_vector.clear();

    int nextCol, nextRow;
	int currentCol,currentRow;

	float x = player->getPositionX();
	float y = player->getPositionY();

	currentCol = x/tiledHeight;
	currentRow = (y - tiledWidth)/tiledWidth;

	pathCols_vector.push_back(currentCol);
	pathRow_vector.push_back(currentRow);


	bool** canPassGrid_copy  = new  bool*[gridRowsCount];  
	 for(int i=0;i<gridRowsCount;i++)
     canPassGrid_copy[i]=new bool [gridColsCount];	

	 

	for(int row = 0;row<gridRowsCount;row++)
	{
		for(int col = 0;col<gridColsCount;col++)
		{
			canPassGrid_copy[row][col] = canPassGrid[row][col];
		}
	}

	int rowtemp = player->getComeFromeRow();
	int coltemp = player->getComeFromCol();
	if(rowtemp <=-1 || coltemp <= -1)
	{
		player->setComeFromCol(currentCol);
		player->setComeFromeRow(currentRow);
	}

	canPassGrid_copy[player->getComeFromeRow()][player->getComeFromCol()] = false;

	std::vector<bool> direction_4;
	std::vector<int> canPassDirVector_temp;

	int hasGoneNumber  = 0;

	while (hasGoneNumber<stepsCount)
	{
		direction_4.clear();
		for(int i=0;i<4;i++)
		{
			direction_4.push_back(false);
		}
		canPassDirVector_temp.clear();

		direction_4[GO_UP]    = isCanGoByColRow(currentRow,currentCol,GO_UP,canPassGrid_copy);
		direction_4[GO_DOWN]  = isCanGoByColRow(currentRow,currentCol,GO_DOWN,canPassGrid_copy);
		direction_4[GO_LEFT]  = isCanGoByColRow(currentRow,currentCol,GO_LEFT,canPassGrid_copy);
		direction_4[GO_RIGHT] = isCanGoByColRow(currentRow,currentCol,GO_RIGHT,canPassGrid_copy);

		for(int i=0;i<4;i++)
		{
			if(direction_4[i])
			{
				canPassDirVector_temp.push_back(i);
			}
		}


		if(canPassDirVector_temp.size() == 0) return;
		int _rand = rand()%canPassDirVector_temp.size(); 

		switch(canPassDirVector_temp[_rand])
		{
			case GO_UP:
				{
					nextRow = currentRow - 1;
                    nextCol = currentCol ;
					break;
				}

		
			case GO_DOWN:
				{
				    nextRow = currentRow +1;
                    nextCol = currentCol;
					break;
				}
			case GO_LEFT:
				{
				    nextRow = currentRow ;
                    nextCol = currentCol - 1;
					break;
				}
			case GO_RIGHT:
				{
					nextRow = currentRow ;
                    nextCol = currentCol + 1;
					break;
				}
		}
	
		pathCols_vector.push_back(nextCol);
		pathRow_vector.push_back(nextRow);

		canPassGrid_copy[currentRow][currentCol] = false;

		currentCol = nextCol;
        currentRow = nextRow;

		hasGoneNumber++;
		
	}
	player->setComeFromCol(pathCols_vector[pathCols_vector.size()-2]);
	player->setComeFromeRow(pathRow_vector[pathRow_vector.size()-2]);

	CC_SAFE_DELETE(canPassGrid_copy);
	direction_4.clear();
	canPassDirVector_temp.clear();
	std::vector<bool>(direction_4).swap(direction_4);
	std::vector<int>(canPassDirVector_temp).swap(canPassDirVector_temp);
}

bool RouteNavigation::isCanGoByColRow(int row,int col,int direction,bool** canPassGrid)
{
	switch(direction)

	{
		case GO_UP:
			{
				return canPassGrid[row -1][col];
			}

		
		case GO_DOWN:
			{
				return canPassGrid[row +1][col];
			}
		case GO_LEFT:
			{
				return canPassGrid[row][col -1];
			}
		case GO_RIGHT:
			{
				return canPassGrid[row][col +1];
			}
	}
       
        return false;

}