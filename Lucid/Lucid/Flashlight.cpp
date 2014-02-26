#include "Flashlight.h"

Flashlight::Flashlight(float x, float y,sf::Color color, int onOff, sf::Texture *texture, float anitmationPicX):
	mTexture(*texture),mColor(color),mAnimationPicX(anitmationPicX) //mLight(mTexture,sf::Vector2f(0,0), mColor)
{

	mRect.left = x;
	mRect.top = y;
	if (onOff == 0)
	{
		mOnOff = false;
	}
	else
	{
		mOnOff = true;
	}
	mLight = new db::Light(mTexture,sf::Vector2f(mRect.left, mRect.top),mColor,mAnimationPicX,mOnOff);
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
