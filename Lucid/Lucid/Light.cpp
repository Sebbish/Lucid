#include "Light.h"
#include <SFML\Graphics\RenderTexture.hpp>

namespace db 
{
	Light::Light( sf::Texture& texture, int typID, sf::Vector2f& position, float width, float height, sf::Color& color, float anitmationPicX, float animationPicY, float onOff, float playerBased, float blink, bool addBlend ) 
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
		else if(typID == 25)
		{
			mAnimationSpeed = 0.11f;
		}
		else
		{
			mAnimationSpeed = 0.15f;
		}

		if ( onOff == 0)
		{
			mOnOff = false;
		}
		else
		{
			mOnOff = true;
		}

		if ( playerBased == 0)
		{
			mPlayerBased = false;
		}
		else
		{
			mPlayerBased = true;
		}

		if ( blink == 0)
		{
			mBlink = false;
		}
		else
		{
			mBlink = true;
		}
		
		mColor = color;
		mAddBlend = addBlend;
		mMoveOnOff = false;
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

		mTypeID = typID;
		mSprite.setTexture( texture );
		mSprite.setPosition( position );
		mSprite.setColor( color );
		mSprite.setScale(mScaleX,mScaleY);
		
		mBlinkTimer = new sf::Clock();
		mBlinkTimerStart = rand() % 24;

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
				if(mAnimationTimer >= mAnimationPicX - mAnimationSpeed)
					mAnimationTimer = 0.0f;
				else
					mAnimationTimer += mAnimationSpeed;
				
			}
			else
			{
				mAnimationPicY = 1;
				if (mTypeID == 58)
				{
					if(mAnimationTimer >= 4 - mAnimationSpeed)
					mAnimationTimer = 0.0f;
					else
					mAnimationTimer += mAnimationSpeed;
				}
				else
				{
					mAnimationTimer = 0.0f;
				}				
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

		if (mBlink == true)
		{
			if (mBlinkStart == true)
			{			
				if (mBlinkTimer->getElapsedTime().asSeconds() >= 2.95 && mBlinkTimer->getElapsedTime().asSeconds() <= 3.35||
					mBlinkTimer->getElapsedTime().asSeconds() >= 3.55 && mBlinkTimer->getElapsedTime().asSeconds() <= 3.65||
					mBlinkTimer->getElapsedTime().asSeconds() >= 3.75 && mBlinkTimer->getElapsedTime().asSeconds() <= 4||
					mBlinkTimer->getElapsedTime().asSeconds() >= 5.55 && mBlinkTimer->getElapsedTime().asSeconds() <= 5.65||
					mBlinkTimer->getElapsedTime().asSeconds() >= 5.75 && mBlinkTimer->getElapsedTime().asSeconds() <= 5.9||
					mBlinkTimer->getElapsedTime().asSeconds() >= 6 && mBlinkTimer->getElapsedTime().asSeconds() <= 6.15||
					mBlinkTimer->getElapsedTime().asSeconds() >= 6.25 && mBlinkTimer->getElapsedTime().asSeconds() <= 6.5||
					mBlinkTimer->getElapsedTime().asSeconds() >= 10.6 && mBlinkTimer->getElapsedTime().asSeconds() <= 10.7||
					mBlinkTimer->getElapsedTime().asSeconds() >= 10.85 && mBlinkTimer->getElapsedTime().asSeconds() <= 11||
					mBlinkTimer->getElapsedTime().asSeconds() >= 11.2 && mBlinkTimer->getElapsedTime().asSeconds() <= 11.3||
					mBlinkTimer->getElapsedTime().asSeconds() >= 11.5 && mBlinkTimer->getElapsedTime().asSeconds() <= 11.6||
					mBlinkTimer->getElapsedTime().asSeconds() >= 11.75 && mBlinkTimer->getElapsedTime().asSeconds() <= 11.9||
					mBlinkTimer->getElapsedTime().asSeconds() >= 13.8 && mBlinkTimer->getElapsedTime().asSeconds() <= 14||
					mBlinkTimer->getElapsedTime().asSeconds() >= 14.1 && mBlinkTimer->getElapsedTime().asSeconds() <= 14.2||
					mBlinkTimer->getElapsedTime().asSeconds() >= 14.3 && mBlinkTimer->getElapsedTime().asSeconds() <= 14.6||
					mBlinkTimer->getElapsedTime().asSeconds() >= 17.05 && mBlinkTimer->getElapsedTime().asSeconds() <= 17.20||
					mBlinkTimer->getElapsedTime().asSeconds() >= 17.3 && mBlinkTimer->getElapsedTime().asSeconds() <= 17.45|| 
					mBlinkTimer->getElapsedTime().asSeconds() >= 17.6 && mBlinkTimer->getElapsedTime().asSeconds() <= 17.75|| 
					mBlinkTimer->getElapsedTime().asSeconds() >= 17.9 && mBlinkTimer->getElapsedTime().asSeconds() <= 20.0)
				{
					mOnOff = false;
				
				}
				else
				{
					mOnOff = true;
				}
			}

			if (mBlinkTimer->getElapsedTime().asSeconds() >= 25.0)
			{
				mBlinkTimer->restart();
			}
		}
		if (mBlinkTimer->getElapsedTime().asSeconds() >= mBlinkTimerStart && mBlinkTimer->getElapsedTime().asSeconds() <= mBlinkTimerStart+1 && mBlinkStart == false)
		{
			mBlinkStart = true;
			mBlinkTimer->restart();
		}

	}

	int Light::getXSize()
	{
		return mRect.width;
	}

	void Light::setBlink(bool blinka)
	{
		mBlink = blinka;
	}

	void Light::setWorldLight(int ambianceRed, int ambianceGreen, int ambianceBlue)
	{
		mAbianceRed = ambianceRed;
		mAbianceGreen = ambianceGreen;
		mAbianceBlue = ambianceBlue;
	}

	int Light::getWorldLightRed()
	{
		return mAbianceRed;
	}

	int Light::getWorldLightGreen()
	{
		return mAbianceGreen;
	}

	int Light::getWorldLightBlue()
	{
		return mAbianceBlue;
	}
}