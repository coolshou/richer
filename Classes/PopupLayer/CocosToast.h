#ifndef __CocosToast_H__
#define __CocosToast_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"


USING_NS_CC;
using namespace std;
typedef void (Layer::*SEL_CallFun)();  
class CocosToast :	public LayerColor
{
public:

	CocosToast(void);
	~CocosToast(void);
	static void createToast(cocos2d::Node *node, const std::string &msg, const float &time,Vec2 point);
	static void createToast(Node* node,const std::string& msg,const float& time,Vec2 point,SEL_CallFun method);
	void removeToast(Node* node);
    void removeToast2(Node* node);
    static SEL_CallFun m_pfnSelectior; 
};

#endif