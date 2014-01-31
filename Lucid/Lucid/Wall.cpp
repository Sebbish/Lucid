#include "Wall.h"

Wall::Wall(sf::FloatRect rect):
	mRect(rect)
{
}

Wall::~Wall()
{
}

void Wall::getFunc(Entity* player)
{
	player->setRect(player->getLastRect());
}

sf::FloatRect Wall::getRect()const
{
	return mRect;
}

void Wall::tick()
{
}

void Wall::render(sf::RenderTexture* window)
{
}