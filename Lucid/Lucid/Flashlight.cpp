#include "Flashlight.h"

Flashlight::Flashlight(float x, float y,sf::Color color, sf::Texture *texture):
	mTexture(*texture),mColor(color) //mLight(mTexture,sf::Vector2f(0,0), mColor)
{

	mRect.left = x;
	mRect.top = y;
	mLight = new db::Light(mTexture,sf::Vector2f(mRect.left, mRect.top),mColor);
//	mLight.setPosition( sf::Vector2f(mRect.left, mRect.top) );
}

Flashlight::~Flashlight()
{

}

sf::FloatRect Flashlight::getRect()const
{
	return mRect;
}

db::Light* Flashlight::render()
{
	return mLight;
}


void Flashlight::setRect(sf::FloatRect rect)
{
	mRect = rect;
}

void Flashlight::setPosition(sf::FloatRect rect)
{
	mRect.left = rect.left;
	mRect.top = rect.top;
}

void Flashlight::setTexture(sf::Texture texture)
{
	mTexture = texture;
}
