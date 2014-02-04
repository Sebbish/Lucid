#include "Light.h"
#include <SFML\Graphics\RenderTexture.hpp>

namespace db 
{
	Light::Light( sf::Texture& texture, sf::Vector2f& position, sf::Color& color, bool addBlend ) 
	{
		mSprite.setTexture( texture );
		mSprite.setPosition( position );
		mSprite.setColor( color );
		mSprite.setScale(3,3);
		mColor = color;
		mAddBlend = addBlend;
	}

	void Light::render( sf::RenderTexture& target ) const
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
}