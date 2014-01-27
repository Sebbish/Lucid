#include "Game.h"

Game::Game()
{
	mWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
    
}

Game::~Game()
{
	delete mWindow;
}

void Game::run()
{
	while (mWindow->isOpen())
    {
        sf::Event event;
        while (mWindow->pollEvent(event))
        {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                mWindow->close();
        }

		tick();

        mWindow->clear();
		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);
        mWindow->draw(shape);

		render();

        mWindow->display();
    }
}

void Game::render()
{

}

void Game::tick()
{

}

void Game::collision()
{

}