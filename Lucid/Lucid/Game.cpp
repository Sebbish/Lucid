#include "Game.h"

Game::Game()
{
	mFH = new FilHanterare();
	mWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	mEntities.push_back(new Player(100,875-768/3,1024/4,768/3,6,mFH->getTexture(0),4));
	camera = new Camera(sf::Vector2f(mWindow->getSize()),mEntities[0]);
	mWindow->setFramerateLimit(60);
	mWindow->setVerticalSyncEnabled(true);
	mMap = new Map(1);
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
	mMap->render(mWindow);
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

void Game::loadMap(std::string filename, int mapID)
{
	delete mMap;
	mMap = new Map(mapID);
	mMap->setTexture(mFH->getTexture(mapID));
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
			direction = dataVector[i + 5]; //0 �r v�nster, 1 �r h�ger
			speed = dataVector[i + 6];
			typeID = dataVector[i + 7];
			mEntities.push_back(new Enemy(x, y, width, height, speed, direction, mFH->getTexture(typeID), typeID)); //skickar int men tar emot float == problem?
			i += 7; //i += x d�r 'x' �r antalet variabler
			break;
		case 2://V�gg
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			mMap->addWall(new Wall(sf::FloatRect(x, y, width, height)));
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
			mMap->addPortal(new Portal(sf::FloatRect(x, y, width, height), targetMapID, targetPortalID, portalID, mFH->getTexture(typeID), typeID));
			i += 8;
			break;
		case 4://NPC
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			dialogueID = dataVector[i + 5];
			typeID = dataVector[i + 6];
			mMap->addNpc(new Npc(sf::FloatRect(x, y, width, height), dialogueID, mFH->getTexture(typeID), typeID));
			i += 6;
			break;
		case 5://Hiding
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			typeID = dataVector[i + 5];
			mMap->addHiding(new Hiding(sf::FloatRect(x, y, width, height), mFH->getTexture(typeID), typeID));
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