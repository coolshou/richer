#ifndef _ELLIPSEBY_H_
#define _ELLIPSEBY_H_

#include "cocos2d.h"

USING_NS_CC;

#define PI 3.14159

//椭圆的参数信息
struct EllipseConfig 
{
	//椭圆a的长度
	float ellipseA;
	//椭圆b的长度
	float ellipseB;
	//椭圆的中心坐标
	Vec2 cenPos;
	//是否逆时针旋转
	bool isAntiClockwise;
	//目标开始旋转的位置，默认位置是在椭圆长轴右方,即值为0
	float startAngle;
	//目标自身的角度
	float selfAngle;
};

class EllipseBy : public ActionInterval
{
public:
	EllipseBy();
	~EllipseBy();

	//初始化函数，参数t为持续时间，config为椭圆参数
	static EllipseBy * create(float t,const EllipseConfig & config);
	bool initWithDuration(float t,const EllipseConfig & config);

	//每帧更新当前椭圆坐标
	virtual void update(float time) override;
	//在动作开始前调用
	virtual void startWithTarget(Node *target) override;
	//动作的拷贝
	virtual EllipseBy * clone() const override;
	//动作的逆序
	virtual EllipseBy * reverse() const override;

protected:
	//获得椭圆上当前点坐标
	inline const Vec2 & getPosWithEllipse(float t)
	{
		float angle = 2 * PI * ((m_config.isAntiClockwise ? t : (1 - t)) + m_config.startAngle / 360);
		return Vec2(m_config.ellipseA * cos(angle),m_config.ellipseB * sin(angle));
	}

private:
	EllipseConfig m_config;
};

#endif