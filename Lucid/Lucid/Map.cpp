#include "Map.h"

Map::Map(int mapID):
	mMapID(mapID)
{
	/*mHidingList.push_back(new Hiding(sf::Vector2f(0, 0), sf::Vector2f(10, 10)));
	mNpcList.push_back(new Npc(sf::Vector2f(0, 100), sf::Vector2f(10, 10), 0));
	mPortalList.push_back(new Portal(sf::Vector2f(0, 200), sf::Vector2f(10, 10), 2, 1, 2));*/
}

Map::~Map()
{
	while (!mHidingList.empty())
	{
		delete mHidingList[mHidingList.size()-1];
		mHidingList.pop_back();
	}

	while (!mPortalList.empty())
	{
		delete mPortalList[mPortalList.size()-1];
		mPortalList.pop_back();
	}

	while (!mSuperPortalList.empty())
	{
		mSuperPortalList.pop_back();
	}

	while (!mNpcList.empty())
	{
		delete mNpcList[mNpcList.size()-1];
		mNpcList.pop_back();
	}

	while (!mWallList.empty())
	{
		delete mWallList[mWallList.size()-1];
		mWallList.pop_back();
	}

	while (!mTriggerList.empty())
	{
		delete mTriggerList[mTriggerList.size()-1];
		mTriggerList.pop_back();
	}

	while (!mParallaxList.empty())
	{
		delete mParallaxList[mParallaxList.size()-1];
		mParallaxList.pop_back();
	}

	while (!mAnimatedObjectList.empty())
	{
		delete mAnimatedObjectList[mAnimatedObjectList.size()-1];
		mAnimatedObjectList.pop_back();
	}
	while (!mRoofList.empty())
	{
		delete mRoofList[mRoofList.size()-1];
		mRoofList.pop_back();
	}
}

void Map::addHiding(Hiding* hiding)
{
	mHidingList.push_back(hiding);
}

void Map::addNpc(Npc* npc)
{
	mNpcList.push_back(npc);
}

void Map::addPortal(Portal* portal)
{
	mPortalList.push_back(portal);
	mSuperPortalList.push_back(portal);
}

void Map::addWall(Wall* wall)
{
	mWallList.push_back(wall);
}

void Map::addTrigger(Trigger* trigger)
{
	mTriggerList.push_back(trigger);
}

void Map::addParallax(Parallax* parallax)
{
	mParallaxList.push_back(parallax);
}

void Map::addAnimatedObject(AnimatedObject* animatedObject)
{
	mAnimatedObjectList.push_back(animatedObject);
}

void Map::addRoof(Roof* roof)
{
	mRoofList.push_back(roof);
}

void Map::setTexture(sf::Texture *texture)
{
	mTexture = texture;
}

std::vector<Object*> Map::getHidingList()const
{
	return mHidingList;
}

std::vector<Object*> Map::getNpcList()const
{
	return mNpcList;
}

std::vector<Object*> Map::getPortalList()const
{
	return mPortalList;
}

std::vector<Portal*> Map::getSuperPortalList()const
{
	return mSuperPortalList;
}

std::vector<Wall*> Map::getWallList()const
{
	return mWallList;
}

std::vector<Trigger*> Map::getTriggerList()const
{
	return mTriggerList;
}

std::vector<Object*> Map::getParallaxList()const
{
	return mParallaxList;
}

std::vector<AnimatedObject*> Map::getAnimatedObjectList()const
{
	return mAnimatedObjectList;
}

std::vector<Object*> Map::getRoofList()const
{
	return mRoofList;
}

std::vector<Object*> Map::getObjectList()const//De man kan trycka E på
{
	std::vector<Object*> objects;
	/*for (auto i:mPortalList)
		objects.push_back(i);*/
	for (auto i:mNpcList)
		objects.push_back(i);
	for (auto i:mHidingList)
		objects.push_back(i);
	/*for (auto i:mAnimatedObjectList)
		objects.push_back(i);*/
	return objects;
}

void Map::tick()
{
	for(auto i:mNpcList)
		i->tick();
	for (auto i:mParallaxList)
		i->tick();
	for (auto i:mAnimatedObjectList)
		i->tick();
	for(auto i:mTriggerList)
		i->tick();
	for (auto i:mPortalList)
		i->tick();
}

void Map::renderMap(sf::RenderTexture* window)
{
	for (auto i:mParallaxList)
		i->render(window);
	for (auto i:mAnimatedObjectList)
	{
		if (i->getLayer() == AnimatedObject::BehindBackground)
			i->render(window);
	}
	sf::RectangleShape r;
	r.setTexture(mTexture);
	//r.setTextureRect(sf::IntRect(0,0,window->getSize().x,window->getSize().y));
	if (mMapID != 1)
		r.setPosition(0,0);
	else
		r.setPosition(2088, 0);
	r.setSize(sf::Vector2f(mTexture->getSize().x,mTexture->getSize().y));
	window->draw(r);
}

void Map::renderObjects(sf::RenderTexture* window)
{
	for (auto i:mAnimatedObjectList)
	{
		if (i->getLayer() == AnimatedObject::BehindObjects)
			i->render(window);
	}
	for (auto i:mHidingList)
		i->render(window);
	for (auto i:mPortalList)
		i->render(window);
	for (auto i:mNpcList)
		i->render(window);
	for (auto i:mAnimatedObjectList)
	{
		if (i->getLayer() == AnimatedObject::InFrontOfObjects)
			i->render(window);
	}
}

void Map::renderForeground(sf::RenderTexture* window)
{
	for (auto i:mAnimatedObjectList)
	{
		if (i->getLayer() == AnimatedObject::Foreground)
			i->render(window);
	}
}

int Map::getID()
{
	return mMapID;
}

void Map::setupPortals()
{
	for (auto i:mSuperPortalList)
	{
		i->setTargetPortal(0);
	}
	for (auto i: mSuperPortalList)
	{
		for (auto j: mSuperPortalList)
		{
			if (i->getTargetPortalID() == j->getPortalID())
			{
				i->setTargetPortal(j);
			}
		}
	}
}