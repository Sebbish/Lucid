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
}

void Map::addWall(Wall* wall)
{
	mWallList.push_back(wall);
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

std::vector<Object*> Map::getWallList()const
{
	return mWallList;
}

void Map::render(sf::RenderWindow* window)
{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	//r.setTextureRect(sf::IntRect(0,0,window->getSize().x,window->getSize().y));
	r.setPosition(0,0);
	r.setSize(sf::Vector2f(window->getSize().x,window->getSize().y));
	window->draw(r);
}