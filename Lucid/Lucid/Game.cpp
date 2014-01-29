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

void Game::loadMap(std::string filename)
{
	std::ifstream stream;
	stream.open(filename);
	std::string output;
	std::vector<int> dataVector;
	int x, y, width, height, typeID, dialogueID, targetMapID, targetPortalID, portalID, speed, direction;
	while(!stream.eof())
	{
		stream >> output;
		dataVector.push_back(atoi(output.c_str()));
	}
	for (int i = 0; i < dataVector.size(); i++)
	{
		switch(dataVector[i])
		{
		case 1://Fiende
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			direction = dataVector[i + 5]; //0 är vänster, 1 är höger
			speed = dataVector[i + 6];
			typeID = dataVector[i + 7];
			mEntities.push_back(new Enemy(x, y, width, height, speed, direction, mFH->getTexture(typeID))); //skickar int men tar emot float == problem?
			i += 7; //i += x där 'x' är antalet variabler
			break;
		case 2://Vägg
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			map.addWall(new Wall(sf::FloatRect(x, y, width, height)));
			i += 4;
			break;
		case 3://Portal
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			targetMapID = dataVector[i + 5];
			targetPortalID = dataVector[i + 6];
			portalID = dataVector[i + 7];
			typeID = dataVector[i + 8];
			map.addPortal(new Portal(sf::FloatRect(x, y, width, height), targetMapID, targetMapID, portalID));
			i += 8;
			break;
		case 4://NPC
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			dialogueID = dataVector[i + 5];
			typeID = dataVector[i + 6];
			map.addPortal(new Portal(sf::FloatRect(x, y, width, height), targetMapID, targetPortalID, portalID));
			i += 6;
			break;
		case 5://Hiding
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			typeID = dataVector[i + 5];
			i += 5;
			break;
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