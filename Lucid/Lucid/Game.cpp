#include "Game.h"


Game::Game()
{
	mWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	mEntities.push_back(new Player(100,100,10,10,2));
}

Game::~Game()
{
	delete mWindow;
}

void Game::run()
{

	mWindow->setFramerateLimit(60);
	while (mWindow->isOpen())
    {
        sf::Event event;
        while (mWindow->pollEvent(event))
        {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                mWindow->close();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				mEntities[0]->setDirection(Entity::RIGHT);
				mEntities[0]->setMove(true);
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				mEntities[0]->setDirection(Entity::LEFT);
				mEntities[0]->setMove(true);
			}else
			{
				mEntities[0]->setMove(false);
			}
        }

		tick();
	
        mWindow->clear();
		/*sf::CircleShape shape(200.f);
		shape.setFillColor(sf::Color::Green);
        mWindow->draw(shape);*/

		render();

        mWindow->display();
    }
}

void Game::render()
{
	for(auto i:mEntities){
		i->render(mWindow);
	}
}

void Game::tick()
{

	for(auto i:mEntities)
	{
		i->tick();
	}
}

void Game::collision()
{

}