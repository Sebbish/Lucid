#ifndef PORTAL_H
#define PORTAL_H

#include "object.h"

class Portal :
	public Object
{
public:
	Portal(sf::FloatRect rect, int targetMapID, int targetPortalID, int portalID, sf::Texture* texture, int typeID);
	~Portal();
	int getTargetMapID()const;
	int getTargetPortalID()const;
	int getPortalID()const;
	virtual sf::FloatRect getRect()const;
	virtual void tick();
	virtual void render(sf::RenderWindow* window);
	virtual void getFunc();
private:
	int mTargetMapID;
	int mTargetPortalID;
	int mPortalID;
	sf::FloatRect mRect;
	int mTypeID;
	sf::Texture* mTexture;
};

#endif

