#include "Game.h"


Game::Game()
{
	mWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	mEntities.push_back(new Player(100,100,10,10,2));
	camera = new Camera(sf::Vector2f(mWindow->getSize()),mEntities[0]);
	mWindow->setFramerateLimit(60);
	mWindow->setVerticalSyncEnabled(true);
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
		sf::CircleShape shape(200.f);
		shape.setFillColor(sf::Color::Green);
		mWindow->setView(*camera->getView());
        mWindow->draw(shape);
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
	camera->tick();
}

void Game::collision()
{
	EntiyVector enteties(mEntities);
	ObjectVector objects(mObjects);

	for (EntiyVector::size_type i = 1; i < enteties.size(); i++)
	{
		Entity *playerEntity = enteties[0];
		Entity *enemyEntity = enteties[i];
		if (overlapsEntity(playerEntity,enemyEntity))
		{
			enteties[i] -> getFunc();
		}
	}
	for (ObjectVector::size_type i = 1; i < objects.size(); i++)
	{
		Entity *playerEntity = enteties[0];
		Object *objectEntity = objects[i];
		if (overlapsObjects(playerEntity,objectEntity))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				objects[i] -> getFunc();
			}
		}
	}
	 
}

bool Game::overlapsEntity(Entity *playerEntity, Entity *otherEntity)
{
	sf::FloatRect playerPosition = playerEntity ->getRect();
	sf::FloatRect otherPosition = otherEntity ->getRect();
	if (playerPosition.intersects(otherPosition))
	return true;
	else
	return false;
}

bool Game::overlapsObjects(Entity *playerEntity, Object *objectEntity)
{
	sf::FloatRect playerPosition = playerEntity ->getRect();
	sf::FloatRect otherPosition = objectEntity ->getRect();
	if (playerPosition.intersects(otherPosition))
	return true;
	else
	return false;
}