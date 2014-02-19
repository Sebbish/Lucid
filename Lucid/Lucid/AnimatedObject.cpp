#include "AnimatedObject.h"


AnimatedObject::AnimatedObject(sf::FloatRect rect, sf::Texture* texture, int typeID, int active, int layer):
	mRect(rect), mTexture(texture), mTypeID(typeID)
{
	mRect.width = texture->getSize().x;
	mRect.height = texture->getSize().y;
	if (active == 0)
		mActive = false;
	else
		mActive = true;
	if (layer == 0)
		mLayer = BehindObjects;
	else if (layer == 1)
		mLayer = InFrontOfObjects;
	else
		layer = Foreground;
	mAlpha = 255;
}


AnimatedObject::~AnimatedObject(void)
{
}

sf::FloatRect AnimatedObject::getRect()const
{
	return mRect;
}

int AnimatedObject::getFunc(Entity* player)
{
	return 0;
}

void AnimatedObject::setActive(bool active)
{
	mActive = active;
}

AnimatedObject::Layer AnimatedObject::getLayer()
{
	return mLayer;
}

int AnimatedObject::getAlpha()
{
	return mAlpha;
}

void AnimatedObject::setAlpha(int alpha)
{
	mAlpha = alpha;
}

void AnimatedObject::tick()
{
}

void AnimatedObject::render(sf::RenderTexture* window)
{
	if (mActive)
	{
		sf::RectangleShape r;
		r.setTexture(mTexture);
		r.setTextureRect(sf::IntRect(0,0,mRect.width,mRect.height));
		r.setPosition(mRect.left,mRect.top);
		r.setSize(sf::Vector2f(mRect.width,mRect.height));
		r.setFillColor(sf::Color(255, 255, 255, mAlpha));
		window->draw(r);
	}
}