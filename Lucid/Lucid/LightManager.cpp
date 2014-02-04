#include "LightManager.h"
#include "Light.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Vector2.hpp>

namespace db
{
	LightManager::LightManager( sf::Vector2i& size )
	{
		mLightMap.create( size.x, size.y );
	}

	void LightManager::setSize( sf::Vector2i& size )
	{
		mLightMap.create( size.x, size.y );
	}

	void LightManager::add( Light* light )
	{
		mLights.push_back( light );
	}

	void LightManager::remove( Light* light )
	{
		for( unsigned i = 0; i < mLights.size(); ++i )
		{
			if( mLights[i] == light )
			{
				mLights.erase( mLights.begin() + i );
			}
		}
	}

	void LightManager::render( sf::RenderWindow& window )
	{
		mLightMap.clear( mAmbient );
		
		for( auto* light : mLights )
		{
			light->render( mLightMap );
		}
		
		mLightMap.display();
		sf::Sprite spriteMap( mLightMap.getTexture() );

		window.draw( spriteMap, sf::BlendMultiply );
	}

	void LightManager::setAmbient( sf::Color& ambient )
	{
		mAmbient = ambient;
	}
}