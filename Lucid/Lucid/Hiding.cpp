#include "Hiding.h"

Hiding::Hiding(sf::Vector2f position, sf::Vector2f size):
	mPosition(position), mSize(size)
{
}

Hiding::~Hiding()
{
}

sf::Vector2f Hiding::getPosition()const
{
	return mPosition;
}

sf::Vector2f Hiding::getSize()const
{
	return mSize;
}