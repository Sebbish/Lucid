#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "Object.h"
#include "Npc.h"
#include "Hiding.h"
#include "Portal.h"

class Map
{
public:
	Map(sf::Texture *texture);
	~Map();
	std::vector<Object*> getHidingList()const;
	std::vector<Object*> getNpcList()const;
	std::vector<Object*> getPortalList()const;
	std::vector<Object*> getWallList()const;
private:
	sf::Texture* mTexture;
	std::vector<Object*> mHidingList, mNpcList, mPortalList, mWallList;
};

#endif
