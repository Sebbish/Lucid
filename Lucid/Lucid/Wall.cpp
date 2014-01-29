#include "Wall.h"

Wall::Wall(sf::FloatRect rect):
	mRect(rect)
{
}

Wall::~Wall()
{
}

sf::FloatRect Wall::getRect()const
{
	return mRect;
}

void Wall::tick()
{
}

void Wall::render(sf::RenderWindow* window)
{
}