#ifndef PORTAL_H
#define PORTAL_H

#include "object.h"

class Portal :
	public Object
{
public:
	Portal(sf::FloatRect rect, int currentMapID, int targetMapID, int targetPortalID, int portalID, sf::Texture* texture, int typeID);
	~Portal();
	int getTargetMapID()const;
	int getTargetPortalID()const;
	int getPortalID()const;
	virtual sf::FloatRect getRect()const;
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
	virtual int getFunc(Entity* player);
	void setTargetPortal(Portal* portal);
private:
	int mCurrentMapID;
	int mTargetMapID;
	int mTargetPortalID;
	int mPortalID;
	sf::FloatRect mRect;
	int mTypeID;
	sf::Texture* mTexture;
	Portal* mTargetPortal;
};

#endif

