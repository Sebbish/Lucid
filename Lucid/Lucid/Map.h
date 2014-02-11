#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "Npc.h"
#include "Hiding.h"
#include "Portal.h"
#include "Wall.h"
#include "Trigger.h"

class Map
{
public:
	Map(int mapID);
	~Map();
	void addHiding(Hiding* hiding);
	void addNpc(Npc* npc);
	void addPortal(Portal* portal);
	void addWall(Wall* wall);
	void addTrigger(Trigger* trigger);
	void setTexture(sf::Texture *texture);
	std::vector<Object*> getHidingList()const;
	std::vector<Object*> getNpcList()const;
	std::vector<Object*> getPortalList()const;
	std::vector<Wall*> getWallList()const;
	std::vector<Trigger*> getTriggerList()const;
	std::vector<Object*> getObjectList()const;
	void tick();
	void renderMap(sf::RenderTexture* window);
	void renderObjects(sf::RenderTexture* window);
	int getID();
	void setupPortals();
private:
	sf::Texture* mTexture;
	std::vector<Object*> mHidingList, mNpcList, mPortalList;
	int mMapID;
	std::vector<Portal*> mSuperPortalList;
	std::vector<Wall*> mWallList;
	std::vector<Trigger*> mTriggerList;
};

#endif
