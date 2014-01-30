#include "Portal.h"

Portal::Portal(sf::FloatRect rect, int targetMapID, int targetPortalID, int portalID, sf::Texture* texture, int typeID):
	mRect(rect), mTargetMapID(targetMapID), mTargetPortalID(targetPortalID), mPortalID(portalID), mTexture(texture), mTypeID(typeID)
{
}

Portal::~Portal()
{
}

void Portal::getFunc()
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
	sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(0,0,mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
}