#ifndef PORTAL_H
#define PORTAL_H

#include "object.h"

class Portal :
	public Object
{
public:
	Portal(sf::Vector2f position, sf::Vector2f size, int targetMapID, int targetPortalID, int portalID);
	~Portal();
	virtual sf::Vector2f getPosition()const;
	virtual sf::Vector2f getSize()const;
	int getTargetMapID()const;
	int getTargetPortalID()const;
	int getPortalID()const;
private:
	sf::Vector2f mPosition;
	sf::Vector2f mSize;
	int mTargetMapID;
	int mTargetPortalID;
	int mPortalID;
};

#endif

