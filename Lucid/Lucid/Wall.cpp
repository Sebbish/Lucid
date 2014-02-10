#include "Wall.h"

Wall::Wall(sf::FloatRect rect):
	mRect(rect)
{
}

Wall::~Wall()
{
}

int Wall::getFunc(Entity* player)
{
	player->setRect(player->getLastRect());
	player->resetTargetX();
	return 0;
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