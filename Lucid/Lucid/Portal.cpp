#include "Portal.h"

Portal::Portal(sf::FloatRect rect, int currentMapID, int targetMapID, int targetPortalID, int portalID, sf::Texture* texture, int typeID, int active, sf::SoundBuffer* portalSound):
	mRect(rect), mCurrentMapID(currentMapID), mTargetMapID(targetMapID), mTargetPortalID(targetPortalID), mPortalID(portalID), mTexture(texture), mTypeID(typeID)
{
	mPortalSound.setBuffer(*portalSound);
	if (active == 0)
		mActive = false;
	else
		mActive = true;
}

Portal::~Portal()
{
}

int Portal::getFunc(Entity* player)
{
	if (mActive)
	{
		if (mTargetPortalID != 0)
		{
			player->setPosition(mTargetPortal->getRect());
			mPortalSound.play();
			return 0;
		}
		else
		{
			return mTargetMapID;
		}
	}
	else
		return 0;
}

sf::FloatRect Portal::getRect()const
{
	return mRect;
}

void Portal::setTargetPortal(Portal* portal)
{
	mTargetPortal = portal;
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

void Portal::setActive(bool active)
{
	mActive = active;
}

void Portal::tick()
{
}

void Portal::render(sf::RenderTexture* window)
{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(0,0,mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
}