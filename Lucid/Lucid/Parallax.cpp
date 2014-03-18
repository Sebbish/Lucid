#include "Parallax.h"

Parallax::Parallax(sf::FloatRect rect, sf::Texture* texture, int typeID, Camera* camera):
	mRect(rect), mTexture(texture), mTypeID(typeID), mCamera(camera)
{
	mRect.width = texture->getSize().x;
	mRect.height = texture->getSize().y;
	mOriginX = rect.left; //Mitten av fönstret
	if (typeID == 32)
		mVariabel = 0.20f;
	else if (typeID == 33)
		mVariabel = 0.15f;
	else if (typeID == 49 || typeID == 50)
		mVariabel = 0.01f;
	else
		mVariabel = 0.25f;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(0,0,mRect.width,mRect.height));
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
}

Parallax::~Parallax(void)
{

}

sf::FloatRect Parallax::getRect()const
{
	return mRect;
}

sf::FloatRect Parallax::getHitBox()const
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
	r.setPosition(mRect.left,mRect.top);
}

void Parallax::render(sf::RenderTexture* window)
{
	window->draw(r);
}