#include "Sanity.h"


Sanity::Sanity(sf::Texture* brus):
	mSanity(100), mBrusTexture(brus)
{
	mWaveShader.loadFromFile("../../../SFML-2.1/examples/shader/resources/wave.vert",sf::Shader::Vertex);
	mAnimationTimer = 0;
	mAnimationSpeed = 0.50;
	mAlpha = 0;
	mBrusAlpha = 0;
	mAlphaSpeed = 2;
	mWaveAmpSpeed = 1;
	mWaveAmp = 0;
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

void Sanity::tick()
{
	mWaveShader.setParameter("wave_phase", clock.getElapsedTime().asSeconds());
	/*if (mSanity < 5)
		mWaveShader.setParameter("wave_amplitude", 0.5 * 25, 0.5 * 50);
	else if (mSanity < 10)
		mWaveShader.setParameter("wave_amplitude", 0.5 * 20, 0.5 * 40);
	else if (mSanity < 15)
		mWaveShader.setParameter("wave_amplitude", 0.5 * 15, 0.5 * 30);
	else if (mSanity < 20)
		mWaveShader.setParameter("wave_amplitude", 0.5 * 10, 0.5 * 20);
	else if (mSanity < 25)
		mWaveShader.setParameter("wave_amplitude", 0.5 * 5, 0.5 * 10);*/

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
}

void Sanity::render(sf::RenderWindow* window)
{
	if (mSanity <= 50 && mAlpha > 0)
	{
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
	if (mSanity < 25)
		return mWaveShader;
	else
		return mEmptyShader;
}

void Sanity::setBrus(bool brus)
{
	mBrus = brus;
}