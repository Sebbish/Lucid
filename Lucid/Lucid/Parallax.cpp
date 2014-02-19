#include "Parallax.h"

Parallax::Parallax(sf::FloatRect rect, sf::Texture* texture, int typeID, Camera* camera):
	mRect(rect), mTexture(texture), mTypeID(typeID), mCamera(camera)
{
	mRect.width = texture->getSize().x;
	mRect.height = texture->getSize().y;
	mOriginX = rect.left;
	if (typeID == 32)
		mVariabel = 0.20f;
	else if (typeID == 33)
		mVariabel = 0.15f;
	else
		mVariabel = 0.25f;

}

Parallax::~Parallax(void)
{

}

sf::FloatRect Parallax::getRect()const
{
	return mRect;
}

int Parallax::getFunc(Entity* player)
{
	return 0;
}

void Parallax::tick()
{
	mRect.left = mOriginX + (mCamera->getView()->getCenter().x - mOriginX) * mVariabel - mTexture->getSize().x / 2;
}

void Parallax::render(sf::RenderTexture* window)
{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(0,0,mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
}