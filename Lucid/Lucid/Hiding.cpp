#include "Hiding.h"

Hiding::Hiding(sf::FloatRect rect, sf::Texture* texture, int typeID):
	mRect(rect), mTexture(texture), mTypeID(typeID)
{
}

Hiding::~Hiding()
{
}

void Hiding::getFunc(Entity* player)
{
	player->toggleHiding();
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
	sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(0,0,mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
}