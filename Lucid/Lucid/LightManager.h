#ifndef DEEPBLUE_LIGHTMANAGER_H
#define DEEPBLUE_LIGHTMANAGER_H

namespace sf 
{
	class RenderWindow;
}

#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\Color.hpp>
#include <SFML\System\Vector2.hpp>
#include <vector>

namespace db 
{
	class Light;
	class LightManager
	{
	public:
		// Initializes the manager
		// @param size: A vector that contains the size of the lightmap.
		LightManager( sf::Vector2i& size );

		// Sets a new size of the lightmap.
		// @param size: A vector that contains the size of the lightmap.
		void setSize( sf::Vector2i& size );

		// Adds a light to the manager.
		// @param light: A light object.
		void add( Light* light );

		// Removes a light from the manager.
		// @param light: A light object.
		void remove( Light* light );


		void setView(sf::View& v);


		// Fills the lightmap with ambient, renders all lights onto it, then renders it to screen.
		// @param window: A RenderWindow to render onto.
		void render( sf::RenderWindow& window );

		// Sets the color to fill the texture with.
		// @param ambient: A color, alpha should always be 255 other channels should be in the range of 8-75.
		void setAmbient( sf::Color& ambient );
	private:
		std::vector< Light* > mLights;
		sf::RenderTexture mLightMap;
		sf::Color mAmbient;
	};
}

#endif