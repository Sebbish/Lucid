#include "Ventilation.h"


Ventilation::Ventilation(int x, int y, int height)
{
	mRect.left = x;
	mRect.top = y;
	mRect.width = 156;
	mRect.height = height;
}


Ventilation::~Ventilation(void)
{
}

int Ventilation::getFunc(Entity* player)
{
	if ((player->getForm() == Entity::ROOFTRAVEL || player->getForm() == Entity::ROOFCHANGING) && player->getRect().left != mRect.left - 50)
	{
		player->setRect(sf::FloatRect(mRect.left - 50, player->getRect().top, player->getRect().width, player->getRect().height));
	}
	return 0;
}

bool Ventilation::getShowE()
{
	return false;
}

sf::FloatRect Ventilation::getRect()const
{
	return mRect;
}

sf::FloatRect Ventilation::getHitBox()const
{
	return mRect;
}

void Ventilation::tick()
{
}

void Ventilation::render(sf::RenderTexture* window)
{
}