#include "Light.h"
#include <SFML\Graphics\RenderTexture.hpp>

namespace db 
{
	Light::Light( sf::Texture& texture, sf::Vector2f& position, sf::Color& color, bool onOff, bool addBlend ) 
	{
		mSprite.setTexture( texture );
		mSprite.setPosition( position );
		mSprite.setColor( color );
		mSprite.setScale(3,3);
		
		mColor = color;
		mAddBlend = addBlend;
		mOnOff = onOff;
	}

	void Light::render( sf::RenderTexture& target ) const
	{
		if (mOnOff == true)
		{
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
			mSprite.setScale(-3,3);
		}
		else
		{
			mSprite.setScale(3,3);
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
}