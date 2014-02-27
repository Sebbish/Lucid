#include "Wall.h"

Wall::Wall(sf::FloatRect rect, int active):
	mRect(rect)
{
	if (active == 0)
		mActive = false;
	else
		mActive = true;
}

Wall::~Wall()
{
}

int Wall::getFunc(Entity* player)
{
	if (mActive)
	{
		player->setRect(player->getLastRect());
		player->resetTargetX();
	}
	return 0;
}

sf::FloatRect Wall::getRect()const
{
	return mRect;
}

sf::FloatRect Wall::getHitBox()const
{
	return mRect;
}

void Wall::tick()
{
}

void Wall::render(sf::RenderTexture* window)
{
}

void Wall::setActive(bool active)
{
	mActive = active;
}