#include "Hiding.h"

Hiding::Hiding(sf::FloatRect rect):
	mRect(rect)
{
}

Hiding::~Hiding()
{
}

sf::FloatRect Hiding::getRect()const
{
	return mRect;
}

void Hiding::tick()
{
}

void Hiding::render(sf::RenderWindow* window)
{
}