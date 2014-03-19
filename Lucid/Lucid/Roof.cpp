#include "Roof.h"


Roof::Roof(sf::FloatRect rect):
	mRect(rect)
{
}


Roof::~Roof(void)
{
}

bool Roof::getShowE()
{
	return false;
}

int Roof::getFunc(Entity* player)
{
	//player->setRect(player->getLastRect());
	player->hitRoof();
	return 0;
}

sf::FloatRect Roof::getRect()const
{
	return mRect;
}

sf::FloatRect Roof::getHitBox()const
{
	return mRect;
}

void Roof::tick()
{
}

void Roof::render(sf::RenderTexture* window)
{
}