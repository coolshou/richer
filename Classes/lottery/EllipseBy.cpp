#include "EllipseBy.h"

EllipseBy::EllipseBy()
{
}

EllipseBy::~EllipseBy()
{
}

EllipseBy * EllipseBy::create(float t,const EllipseConfig & config)
{
	auto pAction = new EllipseBy();
	if (pAction && pAction->initWithDuration(t,config))
	{
		pAction->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pAction);
	}
	return pAction;
}

bool EllipseBy::initWithDuration(float t,const EllipseConfig & config)
{
	if (!ActionInterval::initWithDuration(t))
	{
		return false;
	}
	m_config = config;

	return true;
}

EllipseBy * EllipseBy::clone() const
{
	auto pAction = new EllipseBy();
	pAction->initWithDuration(_duration, m_config);
	pAction->autorelease();
	return pAction;
}

EllipseBy * EllipseBy::reverse() const
{
	EllipseConfig resConfig = m_config;
	resConfig.isAntiClockwise = !m_config.isAntiClockwise;
	return EllipseBy::create(_duration, m_config);
}

void EllipseBy::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);
}

void EllipseBy::update(float time)
{
	if (_target)
	{
		Vec2 curPos = this->getPosWithEllipse(time);
		float tmpAngle = m_config.selfAngle / 180 * PI;
		float newX = curPos.x * cos(tmpAngle) + curPos.y * sin(tmpAngle);
		float newY = curPos.y * cos(tmpAngle) - curPos.x * sin(tmpAngle);
		_target->setPosition(m_config.cenPos + Vec2(newX,newY));
	}
}