/* The two important headers *//*
#include "Light.h"
#include "LightManager.h"

#include <SFML\Graphics.hpp>

/* DEMO OF LIGHT ENGINE *//*
void maisdfgn()
{
	/* Create a lightmanager and give it an initial screensize. *//*
	db::LightManager lm( sf::Vector2i(800,600) );

	/* Load the lightmask texture and the background. */
	/* The quality of the lightmask is basically what defines how "good" the light will look */
	/* One teq. is to SCALE the lightmask x2 or x3 times to give it a better pixelated feel this is not done here though. *//*
	sf::Texture lightMask;
	sf::Texture backgroundTexture;

	lightMask.loadFromFile("glow.png");
	backgroundTexture.loadFromFile("background.png");


	sf::Sprite background(backgroundTexture);



	/*
		Red, Green, Blue and Alpha.
		Alpha should always be full (255) on ambient light!
		Low color values gives a darker light!
		A tiny bit more blue gives a more "real" darkness.
	*//*
	sf::Color ambient(4,4,6,255); 
	lm.setAmbient( ambient );
	/*
		A green light, the higher the other values are, the better blend.
		Tweak for the best result.
		The alpha channel is corresponding to the light intensity.
		178 is a good middle ground, it gives a nice blending but is not to dark.
		Favor brighter colors over brighter light. Tweak for best result.
	*//*
	sf::Color greenLight(55,255,55,178);

	/* Create a light, texture, position and light color. Default value is Add-blending mode. */
	/*
		Add gives a more "real" light, because the colors blend together.
		But normal (alpha) lets other light shine through better.
		No one is BETTER, it depends on the FEEL of the scene.
		It's possible to mix different lights. However I haven't examined the result closely.
	*/
	/* NOTE: Drawing a light multiple times (in add mode) will give it more of a bloom feel. This will need a slight source alteration */
	//db::Light light( lightMask, sf::Vector2f(400,300), greenLight, true );


	/* Add it to the light manager */
	//lm.add( &light );
/*
	sf::RenderWindow window( sf::VideoMode( 800, 600, 32 ), "Light Engine DEMO" );
	window.setFramerateLimit(60);
	sf::Event event;

	while( window.isOpen() )
	{
		while( window.pollEvent( event ) )
		{
		}

		//auto pos = light.getPosition();
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
		{
			pos.y -= 5;
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
		{
			pos.y += 5;
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
		{
			pos.x -= 5;
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
		{
			pos.x += 5;
		}
		light.setPosition(pos);



		window.clear(sf::Color::White);
		window.draw( background );
		/* Draw the lightmap LAST *//*
		lm.render( window );
		window.display();
	}



	//return 0;
}*/