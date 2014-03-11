#include "Flashlight.h"

Flashlight::Flashlight(float x, float y,float width, float height, sf::Color color, int onOff, sf::Texture *texture, int typID, float anitmationPicX, float animationPicY, bool playerBased):
	mTexture(*texture),mColor(color),mAnimationPicX(anitmationPicX), mAnimationPicY(animationPicY) //mLight(mTexture,sf::Vector2f(0,0), mColor)
{

	mRect.left = x;
	mRect.top = y;
	mRect.width = width;
	mRect.height = height;
	if (onOff == 0)
	{
		mOnOff = false;
	}
	else
	{
		mOnOff = true;
	}

	if (playerBased == 0)
	{
		mPlayerBased = false;
	}
	else
	{
		mPlayerBased = true;
	}
	//mLight = new db::Light(mTexture, typID, sf::Vector2f(mRect.left, mRect.top), mRect.width, mRect.height ,mColor,mAnimationPicX, mAnimationPicY, mOnOff, mPlayerBased, );
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
