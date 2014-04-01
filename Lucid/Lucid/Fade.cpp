#include "Fade.h"


Fade::Fade(sf::Texture* texture, sf::RenderTexture &renderTexture):
	mTexture(texture)
{
	mFadeSpeed = 20;
	mSize.x = renderTexture.getSize().x;
	mSize.y = renderTexture.getSize().y;
	mFadeIn = false;
	mFadeOut = false;
	mMapID = 0;
	mAlpha = 0;

	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	r.setPosition(0, 0);
	r.setSize(mSize);
}


Fade::~Fade(void)
{
}

void Fade::render(sf::RenderWindow &window)
{
	
	r.setFillColor(sf::Color(255, 255, 255, mAlpha));
	window.draw(r);
}

void Fade::fadeOut(int newMapID)
{
	if (!mFadeOut)
	{
		mMapID = newMapID;
		mFadeOut = true;
		mFadeIn = false;
		mAlpha = 0;
	}
}

void Fade::fadeIn()
{
	mFadeOut = false;
	mFadeIn = true;
	mAlpha = 255;
}

int Fade::tick()
{
	if (mFadeOut)
	{
		mAlpha += mFadeSpeed;
		if (mAlpha > 255)
		{
			mAlpha = 255;
			mFadeOut = false;
			fadeIn();
			return mMapID;
		}
	}
	else if (mFadeIn)
	{
		mAlpha -= mFadeSpeed;
		if (mAlpha < 0)
		{
			mAlpha = 0;
			mFadeIn = false;
		}
	}
	return 0;
}