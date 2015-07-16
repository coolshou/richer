#ifndef __RICHER_GAME_CONTROLLER_H__
#define __RICHER_GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "RicherPlayer.h"

USING_NS_CC;

const float playerGoTotalTime = 0.28f;
const float playerGoPerFrameTime = 0.07f;
class RicherGameController :public Layer
{
public:
	static RicherGameController* richerGameController_Instance; 
	static RicherGameController* getInstance();
	~RicherGameController();
	void startRealGo(std::vector<int> rowVector,std::vector<int> colVector,RicherPlayer* richerPlayer);
	void endGo();
	CREATE_FUNC(RicherGameController);
	 virtual bool init();   

	 void pickOnePlayerToGo();

private :
	int stepHasGone ;
	int stepsCount ;
	bool isAnimFinished;
	int nextRow ;
	int nextCol ;
	int currentRow ;
	int currentCol ;
	MoveBy* moveBy;
	Repeat* repeate;
	Action* spawnAction;
	CallFunc* callEndGoFunc;
	void moveOneStep(RicherPlayer* richerPlayer);
	void resetPlayerGoTurn();
	std::vector<int> _rowVector;
	std::vector<int> _colVector;
	RicherPlayer* _richerPlayer;

	void sendMsgForGo();
	void handlePropEvent();
	void registerNotificationObserver();
	void receivedMsg(Object* data);
	bool oneRoundDone;
	float** positionAroundEnd;
	void aroundLandEvent();
};

#endif