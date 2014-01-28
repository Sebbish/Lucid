#include "Wall.h"

Wall::Wall(sf::Vector2f position, sf::Vector2f size):
	mPosition(position), mSize(size)
{
}

Wall::~Wall()
{
}

sf::Vector2f Wall::getPosition()const
{
	return mPosition;
}

sf::Vector2f Wall::getSize()const
{
	return mSize;
}