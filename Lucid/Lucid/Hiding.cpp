#include "Hiding.h"

Hiding::Hiding(sf::FloatRect rect, sf::Texture* texture, int typeID):
	mRect(rect), mTexture(texture), mTypeID(typeID)
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