#ifndef __STOCK_H__
#define __STOCK_H__
#include "cocos2d.h"
USING_NS_CC;

class Stock : public Sprite
{
public:
	Stock(int stockCode, String* stockName,int nowPrice,int makedealprice,float percent ,int storeNumber);
	~Stock(void);
	static Stock* create(int stockCode,  String* stockName,int nowPrice,int makedealprice,float percent ,int storeNumber);

	void setCode(int stockCode);
	int getCode();

	void setStockName(String* stockName);
	String* getStockName();

	void setNowPrice( int nowPrice);
	int getNowPrice();

	void setMakedealprice(int makedealprice);
	int getMakedealprice();

	void setPercent(float percent);
	float getPercent();

	void setStoreNumber(int storeNumber);
	int getStoreNumber();

private:
	int stockCode;
	String* stockName;
    int nowPrice;
    int makedealprice;
	float percent;

	int storeNumber;
};

#endif