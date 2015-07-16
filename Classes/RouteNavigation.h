#ifndef _ROUTE_NAV_H_
#define _ROUTE_NAV_H_

#include "cocos2d.h"
#include "RicherPlayer.h"

USING_NS_CC;


const int GO_UP = 0;
const int GO_DOWN = 1;
const int GO_LEFT = 2;
const int GO_RIGHT = 3;

class RouteNavigation{
public:
	static RouteNavigation* routeNav_Instance; 
	static RouteNavigation* getInstance();
	void getPath(RicherPlayer* player,int stepsCount,bool** canPassGrid,int gridRowsCount,int gridColsCount);
	bool isCanGoByColRow(int row,int col,int direction,bool** canPassGrid);
protected:
	 RouteNavigation(void);
	~RouteNavigation(void);
private :
	CC_SYNTHESIZE(std::vector<int>, pathCols_vector, PathCols_vector);
	CC_SYNTHESIZE(std::vector<int>, pathRow_vector, PathRow_vector);
};

#endif