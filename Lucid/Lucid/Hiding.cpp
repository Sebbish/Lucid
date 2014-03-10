#include "Hiding.h"

Hiding::Hiding(sf::FloatRect rect, sf::Texture* texture, int typeID):
	mRect(rect), mTexture(texture), mTypeID(typeID)
{
}

Hiding::~Hiding()
{
}

int Hiding::getFunc(Entity* player)
{
	player->toggleHiding();
	return 0;
}

sf::FloatRect Hiding::getRect()const
{
	return mRect;
}

sf::FloatRect Hiding::getHitBox()const
{
	sf::FloatRect hitBoxRect = mRect;
	hitBoxRect.left += 115;
	hitBoxRect.top += 26;
	hitBoxRect.height = 230;
	hitBoxRect.width = 26;
	return hitBoxRect;
}


void Hiding::tick()
{
}

void Hiding::render(sf::RenderTexture* window)
{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(0,0,mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
}