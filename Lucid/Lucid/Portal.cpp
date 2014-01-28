#include "Portal.h"

Portal::Portal(sf::Vector2f position, sf::Vector2f size, int targetMapID, int targetPortalID, int portalID):
	mPosition(position), mSize(size), mTargetMapID(targetMapID), mTargetPortalID(targetPortalID), mPortalID(portalID)
{
}

Portal::~Portal()
{
}

sf::Vector2f Portal::getPosition()const
{
	return mPosition;
}

sf::Vector2f Portal::getSize()const
{
	return mSize;
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