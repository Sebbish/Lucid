#include "Game.h"


Game::Game()
{
	mFH = new FilHanterare();
	mWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	mEntities.push_back(new Player(100,875-768/3,1024/4,768/3,6,mFH->getTexture(0),4));
	camera = new Camera(sf::Vector2f(mWindow->getSize()),mEntities[0]);
	mWindow->setFramerateLimit(60);
	mWindow->setVerticalSyncEnabled(true);
	map = new Map(mFH->getTexture(1));
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
		mousePositionFunc();

        mWindow->display();
    }
}

void Game::render()
{
	map->render(mWindow);
	for(auto i:mEntities){
		i->render(mWindow);
	}
}

void Game::tick()
{
	mMousePosition = sf::Mouse::getPosition();
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
		if (overlapsMouse(enemyEntity))
		{

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

bool Game::overlapsMouse(Entity *entity)
{
	sf::Vector2i mMousePosition = sf::Mouse::getPosition();
	sf::FloatRect mousePosition;
	mousePosition.left = mMousePosition.x;
	mousePosition.top  = mMousePosition.y;
	sf::FloatRect otherPosition = entity ->getRect();
	if (mousePosition.intersects(otherPosition))
	return true;
	else
	return false;
}

void Game::mousePositionFunc()
{
	int mouseX = 0;
	int mouseY = 0;
	sf::RectangleShape mouseRect;
	mouseRect.setPosition(mMousePosition.x-380 - mouseX,mMousePosition.y-440 - mouseY);
	mouseRect.setSize(sf::Vector2f(15,15));
	mWindow -> draw(mouseRect);
}