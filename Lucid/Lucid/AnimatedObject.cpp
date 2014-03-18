#include "AnimatedObject.h"


AnimatedObject::AnimatedObject(sf::FloatRect rect, sf::Texture* texture, int typeID, int active, int layer, int animationY, int animationPicX, int direction, int alpha, int animate, int loop):
	mRect(rect), mTexture(texture), mTypeID(typeID), mAlpha(alpha)
{
	/*mRect.width = texture->getSize().x;
	mRect.height = texture->getSize().y;*/
	if (active == 0)
		mActive = false;
	else
		mActive = true;
	if (layer == 0)
		mLayer = BehindBackground;
	else if (layer == 1)
		mLayer = BehindObjects;
	else if (layer == 2)
		mLayer = InFrontOfObjects;
	else
		mLayer = Foreground;

	if (animate == 0)
		mAnimate = false;
	else
		mAnimate = true;
	if (loop == 0)
		mLoop = false;
	else
		mLoop = true;


	mAnimationY = animationY;
	mAnimationPicX = animationPicX;
	mAnimationTimer = 0.0f;

	if (typeID == 35)
	{
		mAnimationSpeed = 0.2f;
	}
	if (typeID == 36)
	{
		mAnimationSpeed = 0.75f;
	}
	if (typeID == 44)
	{
		mAnimationSpeed = 0.1f;
	}
	else
		mAnimationSpeed = 0.15f;

	if (direction == 0)
	{
		mAnimationDirection = Forward;
	}
	else
	{
		mAnimationDirection = Backward;
		mAnimationSpeed = -mAnimationSpeed;
		mAnimationTimer = mAnimationPicX + mAnimationSpeed;
	}

	//mAnimate = false;
	//mLoop = false;
	mFadeIn = false;
	mFadeOut = false;
	mFadeSpeed = 20;
	r.setTexture(mTexture);
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	r.setTextureRect(sf::IntRect(mRect.width*(int)mAnimationTimer, mAnimationY * mRect.height,mRect.width,mRect.height));
	r.setFillColor(sf::Color(255, 255, 255, mAlpha));
}


AnimatedObject::~AnimatedObject(void)
{
}

sf::FloatRect AnimatedObject::getRect()const
{
	return mRect;
}

sf::FloatRect AnimatedObject::getHitBox()const
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

void AnimatedObject::setAnimate(bool animate)
{
	mAnimate = animate;
}

void AnimatedObject::setLoop(bool loop)
{
	mLoop = loop;
}

void AnimatedObject::fadeout()
{
	mFadeOut = true;
	mFadeIn = false;
}

void AnimatedObject::fadein()
{
	mFadeIn = true;
	mFadeOut = false;
}

void AnimatedObject::tick()
{
	if (mAnimate)
	{
		if((mAnimationTimer >= mAnimationPicX - mAnimationSpeed && mAnimationDirection == Forward) || (mAnimationTimer <= 0.0f - mAnimationSpeed && mAnimationDirection == Backward))
		{
			if (mLoop)
			{
				if (mAnimationDirection == Forward)
					mAnimationTimer = 0.0f;
				else
					mAnimationTimer = mAnimationPicX + mAnimationSpeed;

			}
			else
			{
				mAnimate = false;
			}
		}
		else
		{
			mAnimationTimer += mAnimationSpeed;
		}

		r.setTextureRect(sf::IntRect(mRect.width*(int)mAnimationTimer, mAnimationY * mRect.height,mRect.width,mRect.height));
	}

	//Fade
	if (mFadeOut && mAlpha > 0)
		mAlpha -= mFadeSpeed;
	else
		mFadeOut = false;

	if (mAlpha < 0)
		mAlpha = 0;

	if (mFadeIn && mAlpha < 255)
		mAlpha += mFadeSpeed;
	else
		mFadeIn = false;
	if (mAlpha > 255)
		mAlpha = 255;

	if(mFadeIn || mFadeOut)
		r.setFillColor(sf::Color(255, 255, 255, mAlpha));
}

void AnimatedObject::render(sf::RenderTexture* window)
{
	if (mActive)
	{
		window->draw(r);
	}
}