#include "Map.h"

Map::Map(sf::Texture *texture):
	mTexture(texture)
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