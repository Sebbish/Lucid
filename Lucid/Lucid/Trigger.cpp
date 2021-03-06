#include "Trigger.h"


Trigger::Trigger(sf::FloatRect rect, int triggedByID, int active):
	mRect(rect), mTriggedByID(triggedByID)
{
	mTrigged = false;
	if (active == 0)
		mActive = false;
	else
		mActive = true;
}


Trigger::~Trigger(void)
{
}

bool Trigger::getShowE()
{
	return false;
}

int Trigger::getFunc(Entity* player)
{
	if (mActive && player->getTypeID() == mTriggedByID)
	{
		mTrigged = true;
	}
	return 0;
}

sf::FloatRect Trigger::getRect()const
{
	return mRect;
}

sf::FloatRect Trigger::getHitBox()const
{
	return mRect;
}


void Trigger::tick()
{
	mTrigged = false;
}

void Trigger::render(sf::RenderTexture* window)
{
}

void Trigger::setActive(bool active)
{
	mActive = active;
}

bool Trigger::getTrigged()
{
	if (mActive && mTrigged)
		return true;
	else
		return false;
}

bool Trigger::getActive()
{
	return mActive;
}

void Trigger::setRect(sf::FloatRect rect)
{
	mRect = rect;
}