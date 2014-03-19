#ifndef PORTAL_H
#define PORTAL_H

#include "object.h"

class Portal :
	public Object
{
public:
	Portal(sf::FloatRect rect, int currentMapID, int targetMapID, int targetPortalID, int portalID, sf::Texture* texture, int typeID, int active, int useTexture, int direction, sf::SoundBuffer* portalSound);
	~Portal();
	int getTargetMapID()const;
	int getTargetPortalID()const;
	int getPortalID()const;
	virtual sf::FloatRect getRect()const;
	virtual sf::FloatRect getHitBox()const;
	virtual bool getShowE();
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
	virtual int getFunc(Entity* player);
	void setTargetPortal(Portal* portal);
	void setActive(bool active);
	Portal* getTargetPortal();
	bool getActive();
private:
	int mCurrentMapID;
	int mTargetMapID;
	int mTargetPortalID;
	int mPortalID;
	sf::FloatRect mRect;
	int mTypeID;
	sf::Texture* mTexture;
	Portal* mTargetPortal;
	sf::Sound mPortalSound;
	bool mActive;
	bool mUseTexture;
	bool mOpened;

	float mAnimationTimer;
	int mAnimationPicX;
	float mAnimationSpeed;
	bool mAnimate;

	bool directionRight;
};

#endif

