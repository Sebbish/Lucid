#include "Portal.h"

Portal::Portal(sf::FloatRect rect, int targetMapID, int targetPortalID, int portalID):
	mRect(rect), mTargetMapID(targetMapID), mTargetPortalID(targetPortalID), mPortalID(portalID)
{
}

Portal::~Portal()
{
}
sf::FloatRect Portal::getRect()const
{
	return mRect;
}

int Portal::getTargetMapID()const
{
	return mTargetMapID;
}

int Portal::getTargetPortalID()const
{
	return mTargetPortalID;
}

int Portal::getPortalID()const
{
	return mPortalID;
}

void Portal::tick()
{
}

void Portal::render(sf::RenderWindow* window)
{
}