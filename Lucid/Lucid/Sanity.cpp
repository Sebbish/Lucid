#include "Sanity.h"


Sanity::Sanity(sf::Texture* brus):
	mSanity(100), mBrusTexture(brus)
{
	mWaveShader.loadFromFile("../../../SFML-2.1/examples/shader/resources/wave.vert", "../../../SFML-2.1/examples/shader/resources/blur.frag");
	mAnimationTimer = 0;
	mAnimationSpeed = 0.50;
	mAlpha = 0;
	mBrusAlpha = 0;
	mAlphaSpeed = 2;
	mWaveAmpSpeed = 1;
	mWaveAmp = 0;
	mDelayTimer = 0;
	mWhiteFadeIn = false;
	mWhiteFadeOut = false;
}


Sanity::~Sanity()
{
}

float Sanity::getSanity()const
{
	return mSanity;
}

void Sanity::setSanity(float sanity)
{
	mSanity += sanity;
}

void Sanity::die()
{
	mWhiteFadeOut = true;
	mWhiteFadeIn = false;
}

void Sanity::live()
{
	mBlurValue = 0;
	mWhiteFadeIn = true;
	mWhiteFadeOut = false;
}

bool Sanity::fadeIsDone()
{
	if (mDieFade >= 255)
		return true;
	else
		return false;
}

void Sanity::tick()
{
	//Wave
	mWaveShader.setParameter("wave_phase", clock.getElapsedTime().asSeconds());

	if (mSanity >= 50)
		mBrusAlpha = 0;
	else if (mSanity >= 0)
		mBrusAlpha = 50 - mSanity;
	else
		mBrusAlpha = 50;

	if (mWaveAmp < mBrusAlpha && mBrus)
		mWaveAmp += mWaveAmpSpeed;
	else
		mWaveAmp -= mWaveAmpSpeed;
	if (mWaveAmp > 50)
		mWaveAmp = 50;
	else if (mWaveAmp < 0)
		mWaveAmp = 0;
	mWaveShader.setParameter("wave_amplitude", 0.5 * mWaveAmp / 2, 0.5 * mWaveAmp);

	mBrusAlpha *= 5;

	if (mAlpha < mBrusAlpha && mBrus)
		mAlpha += mAlphaSpeed;
	else
		mAlpha -= mAlphaSpeed;
	if (mAlpha > 255)
		mAlpha = 255;
	else if (mAlpha < 0)
		mAlpha = 0;

	if (mAnimationTimer >= 4 - mAnimationSpeed)
	{
		mAnimationTimer = 0;
	}
	else
	{
		mAnimationTimer += mAnimationSpeed;
	}

	//Blur
	if (mWhiteFadeOut)
	{
		if (mDelayTimer > 50)
		{
			mBlurValue += 0.01;
			mDieFade += 20;
		}
		else
			mDelayTimer++;
	}
	/*else
	{
		mBlurValue = 0;
		mDieFade = 0;
	}*/

	if (mWhiteFadeIn)
	{
		if (mDieFade > 0);
		{
			mDieFade -= 2;
		}
	}
	if (mDieFade < 0)
		mDieFade = 0;
	else if (mDieFade > 255)
		mDieFade = 255;
	mWaveShader.setParameter("blur_radius", mBlurValue * 0.004f);
}

void Sanity::render(sf::RenderWindow* window)
{
	if (mDieFade != 0)
	{
		sf::RectangleShape r;
		r.setPosition(0,0);
		r.setSize(sf::Vector2f(1920,1080));
		r.setTexture(mDieTexture);
		r.setTextureRect(sf::IntRect(0,0,1920,1080));
		r.setFillColor(sf::Color(255, 255, 255, (int)mDieFade));
		window->draw(r);
	}
	if ((mSanity <= 50 && mAlpha > 0) || mWhiteFadeOut)
	{
		if (mWhiteFadeOut && mBrus && mAlpha < mDieFade)
			mAlpha = mDieFade;
		else if (mWhiteFadeOut && !mBrus)
			mAlpha = mDieFade;
		sf::RectangleShape r;
		r.setPosition(0,0);
		r.setSize(sf::Vector2f(1920,1080));
		r.setTexture(mBrusTexture);
		r.setTextureRect(sf::IntRect(1920*(int)mAnimationTimer,0,1920,1080));
		r.setFillColor(sf::Color(255, 255, 255, (int)mAlpha));
		window->draw(r);
	}
}

sf::Shader& Sanity::getShader()
{
	if (mSanity < 25 || mWhiteFadeOut)
		return mWaveShader;
	else
		return mEmptyShader;
}

void Sanity::setBrus(bool brus)
{
	mBrus = brus;
}