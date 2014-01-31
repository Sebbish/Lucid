#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "Object.h"
#include "Npc.h"
#include "Hiding.h"
#include "Portal.h"
#include "Wall.h"

class Map
{
public:
	Map(int mapID);
	~Map();
	void addHiding(Hiding* hiding);
	void addNpc(Npc* npc);
	void addPortal(Portal* portal);
	void addWall(Wall* wall);
	void setTexture(sf::Texture *texture);
	std::vector<Object*> getHidingList()const;
	std::vector<Object*> getNpcList()const;
	std::vector<Object*> getPortalList()const;
	std::vector<Object*> getWallList()const;
	std::vector<Object*> getObjectList()const;
	void renderMap(sf::RenderWindow* window);
	void renderObjects(sf::RenderWindow* window);
	int getID();
	void setupPortals();
private:
	sf::Texture* mTexture;
	std::vector<Object*> mHidingList, mNpcList, mPortalList, mWallList;
	int mMapID;
	std::vector<Portal*> mSuperPortalList;
};

#endif
