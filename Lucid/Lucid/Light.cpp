#include "Light.h"
#include <SFML\Graphics\RenderTexture.hpp>

namespace db 
{
	Light::Light( sf::Texture& texture, int typID, sf::Vector2f& position, float width, float height, sf::Color& color, float anitmationPicX, float animationPicY, bool onOff, bool playerBased, bool addBlend ) 
	{
		
		mScaleX = 1;
		mScaleY = 1;
		mAnimationPicX = anitmationPicX;
		mAnimationPicY = animationPicY;
		mAnimationTimer = 0.0f;

		if (typID  == 43)
		{
			mAnimationSpeed = 0.1f;
		}
		else
		{
			mAnimationSpeed = 0.15f;
		}
		
		mColor = color;
		mAddBlend = addBlend;
		mOnOff = onOff;
		mMoveOnOff = false;
		mPlayerBased = playerBased;
		mRect.height = texture.getSize().y;
		mRect.width = texture.getSize().x;
		mRect.left = position.x;
		mRect.top = position.y;
		mRect.width = width;
		mRect.height = height;
		mDirection = RIGHT;
		mAbianceRed = 0;
		mAbianceBlue = 0;
		mAbianceGreen = 0;

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
				mSprite.setTextureRect(sf::IntRect (mRect.width*(int)mAnimationTimer, mAnimationPicY * mRect.height,mRect.width,mRect.height));
			else if(mDirection == LEFT)
				mSprite.setTextureRect(sf::IntRect(mRect.width*((int)mAnimationTimer+1),mAnimationPicY * mRect.height,-mRect.width,mRect.height));

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

	void Light::setMoveOnOff(bool moveOnOff)
	{
		mMoveOnOff = moveOnOff;
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

	void Light::tick()
	{
		if (mPlayerBased == true)
		{
			if (mMoveOnOff == true )
			{
				mAnimationPicY = 0;
				if(mAnimationTimer >= mAnimationPicX-mAnimationSpeed)
					mAnimationTimer = 0.0f;
				else
					mAnimationTimer += mAnimationSpeed;
				
			}
			else
			{
				mAnimationPicY = 1;
				mAnimationTimer = 0.0f;
				
			}
		}
		else if (mPlayerBased == false)
		{
			if (mMoveOnOff == true )
			{
				mAnimationPicY = 0;
				if(mAnimationTimer >= mAnimationPicX-mAnimationSpeed)
					mAnimationTimer = 0.0f;
				else
					mAnimationTimer += mAnimationSpeed;
			}
			else
			{
				mAnimationPicY = 0;
				mAnimationTimer = 0.0f;
			}
			
		}
		else
		{
			mAnimationPicY = 0;
			mAnimationTimer = 0.0f;
		}

	}

	int Light::getXSize()
	{
		return mRect.width;
	}

	void Light::setWorldLight(int ambianceRed, int ambianceGreen, int ambianceBlue)
	{
		mAbianceRed = ambianceRed;
		mAbianceGreen = ambianceGreen;
		mAbianceBlue = ambianceBlue;
	}

	sf::Color Light::getWorldLight()
	{
		sf::Color colorSet(mAbianceRed,mAbianceGreen,mAbianceBlue,255);
		return colorSet;
	}
}