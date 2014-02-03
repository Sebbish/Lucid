#ifndef DEEPBLUE_LIGHT_H
#define DEEPBLUE_LIGHT_H

namespace sf
{
	class Texture;
	class RenderTexture;
}

#include <SFML\Graphics\Color.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Vector2.hpp>

namespace db 
{
	class Light
	{
	public:
		// Initializes the light.
		// @param texture: Masking texture for the light.
		// @param position: Position of where to draw the light.
		// @param color: Color of the light, alpha is intensity.
		// @param addBlend: Draw light with addaptive blending or not.
		Light( sf::Texture& texture, sf::Vector2f& position, sf::Color& color, bool addBlend = true );

		// Renders the light.
		// @param target: The texture of which to render onto.
		void render( sf::RenderTexture& target ) const;

		// Retrives the light position.
		// @return: A vector containing position, expressed in float.
		sf::Vector2f getPosition() const;

		// Retrives the color of the light.
		// @return: Color of the light, alpha is intensity.
		sf::Color getColor() const;

		// Sets the position of the light.
		// @param position: A vector containing position, expressed in float.
		void setPosition( sf::Vector2f& position );

		// Retrives the color of the light.
		// @param color: Color of the light, alpha is intensity.
		void setColor( sf::Color& color );
	private:
		sf::Sprite mSprite;
		sf::Color mColor;
		bool mAddBlend;
	};
}


#endif