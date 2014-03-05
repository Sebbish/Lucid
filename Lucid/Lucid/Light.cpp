#include "Light.h"
#include <SFML\Graphics\RenderTexture.hpp>

namespace db 
{
	Light::Light( sf::Texture& texture, sf::Vector2f& position, sf::Color& color, float anitmationPicX, bool onOff, bool addBlend ) 
	{
		
		mScaleX = 1;
		mScaleY = 1;
		mAnimationPicX = anitmationPicX;
		mAnimationPicY = 0.0f;
		mAnimationTimer = 0.0f;
		mAnimationSpeed = 0.15f;
		mColor = color;
		mAddBlend = addBlend;
		mOnOff = onOff;
		mRect.height = texture.getSize().y;
		mRect.width = texture.getSize().x;
		mRect.left = position.x;
		mRect.top = position.y;

		mSprite.setTexture( texture );
		mSprite.setPosition( position );
		mSprite.setColor( color );
		mSprite.setScale(mScaleX,mScaleY);
		//mSprite.setTextureRect(sf::IntRect (mRect.width*(int)mAnimationTimer, mRect.height,mRect.width,mRect.height));
	}

	void Light::render( sf::RenderTexture& target ) 
	{
		if (mOnOff == true)
		{
			if(mDirection == RIGHT)
				mSprite.setTextureRect(sf::IntRect (mRect.width/mAnimationPicX*(int)mAnimationTimer, mAnimationPicY * mRect.height/2,mRect.width/mAnimationPicX,mRect.height));
			else if(mDirection == LEFT)
				mSprite.setTextureRect(sf::IntRect(mRect.width/mAnimationPicX*((int)mAnimationTimer+1),mAnimationPicY * mRect.height/2,-mRect.width/mAnimationPicX,mRect.height));

			if(mAddBlend)
			{
				target.draw( mSprite, sf::BlendAdd );
			}
			else
			{
				target.draw( mSprite );
			}
		}
	}

	sf::Vector2f Light::getPosition() const
	{
		return mSprite.getPosition();
	}

	sf::Color Light::getColor() const
	{
		return mSprite.getColor();
	}

	void Light::setPosition( sf::Vector2f& position )
	{
		mSprite.setPosition( position );
	}

	void Light::setColor( sf::Color& color )
	{
		mSprite.setColor( color );
	}

	void Light::flipSprite(int direction)
	{
		if (direction == 0)
		{
			mDirection = LEFT;
		}
		else
		{
			mDirection = RIGHT;
		}
	}

	void Light::setOnOff(bool onOff)
	{
		mOnOff = onOff;
	}

	bool Light::getOnOff()
	{
		return mOnOff;
	}

	void Light::setScale(float x, float y)
	{
		mScaleX = x;
		mScaleY = y;
		mSprite.setScale(mScaleX,mScaleY);
	}

	void Light::tick(bool moveOnOff)
	{
		if (moveOnOff == true)
		{
			if(mAnimationTimer >= mAnimationPicX-mAnimationSpeed)
				mAnimationTimer = 0.0f;
			else
				mAnimationTimer += mAnimationSpeed;
			mAnimationPicY = 0.0f;
		}
		else
		{
			mAnimationTimer = 0.0f;
			mAnimationPicY = 1.0f;
		}

	}

	int Light::getXSize()
	{
		return mRect.width/mAnimationPicX;
	}
}