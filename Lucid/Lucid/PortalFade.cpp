#include "PortalFade.h"


PortalFade::PortalFade(sf::Texture* texture, sf::RenderTexture &renderTexture):
	mTexture(texture)
{
	mFadeSpeed = 20;
	mSize.x = renderTexture.getSize().x;
	mSize.y = renderTexture.getSize().y;
	mFadeIn = false;
	mFadeOut = false;
	mAlpha = 0;
	mPosition = sf::FloatRect(0, 0, 0, 0);
	mWaitTime = 0;
}


PortalFade::~PortalFade(void)
{
}

void PortalFade::render(sf::RenderWindow &window)
{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	r.setPosition(0, 0);
	r.setSize(mSize);
	if (mAlpha < 255)
		r.setFillColor(sf::Color(255, 255, 255, mAlpha));
	else
		r.setFillColor(sf::Color(255, 255, 255, 255));
	window.draw(r);
}

void PortalFade::fadeOut(sf::FloatRect position)
{
	if (!mFadeOut)
	{
		mPosition = position;
		mFadeOut = true;
		mFadeIn = false;
		mAlpha = 0;
	}
}

void PortalFade::fadeIn()
{
	mFadeOut = false;
	mFadeIn = true;
	mAlpha = 255;
}

sf::FloatRect PortalFade::tick()
{
	if (mFadeOut)
	{
		mAlpha += mFadeSpeed;
		if (mAlpha > 255 + mWaitTime)
		{
			fadeIn();
			return mPosition;
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
	return sf::FloatRect(0, 0, 0, 0);
}