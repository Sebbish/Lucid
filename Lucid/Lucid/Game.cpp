#include "Game.h"

Game::Game()
{
	angle = 0;
	mFH = new FilHanterare();
	mWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	mEntities.push_back(new Player(1200,875-768/3,1024/4,768/3,6,mFH->getTexture(0),4));
	camera = new Camera(sf::Vector2f(mWindow->getSize()),mEntities[0]);
	mWindow->setFramerateLimit(60);
	mWindow->setVerticalSyncEnabled(true);
	loadMap("../Debug/map1.txt", 1);

	//ladda shader
	//mShader.loadFromFile("P:/SFML-2.1/examples/shader/resources/edge.frag",sf::Shader::Fragment);
	//mShader.loadFromFile("P:/SFML-2.1/examples/shader/resources/wave.vert","P:/SFML-2.1/examples/shader/resources/blur.frag");

	//fixar edge shader*/
	//mShader.setParameter("texture", sf::Shader::CurrentTexture);

}

Game::~Game()
{
	delete mWindow;
}

void Game::run()
{
	while (mWindow->isOpen())
    {
		input(mEntities[0]);
		tick();
	
		mWindow->clear(sf::Color(255, 0, 255));
		mWindow->setView(*camera->getView());
		render();
		//mousePositionFunc();
        mWindow->display();
    }
}

void Game::input(Entity* entity)
{
	sf::Event event;
        while (mWindow->pollEvent(event))
        {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                mWindow->close();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				entity->setDirection(Entity::RIGHT);
				entity->setMove(true);
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				entity->setDirection(Entity::LEFT);
				entity->setMove(true);
			}else
			{
				entity->setMove(false);
			}
    }
}



void Game::render()
{
	mRenderTexture.clear();
	mMap->renderMap(&mRenderTexture);
	for(auto i:mEntities){
		if (i -> getLayer() == Entity::Back)
			i->render(&mRenderTexture);
	}
	mMap -> renderObjects(&mRenderTexture);
	for(auto i:mEntities){
		if (i -> getLayer() == Entity::Front)
			i->render(&mRenderTexture);
	}
	mRenderTexture.display();
	const sf::Texture& s = mRenderTexture.getTexture();
	sf::Sprite ss;
	ss.setTexture(s);
	mWindow->draw(ss,&mShader);
}

void Game::tick()
{
	/*mMousePosition = sf::Mouse::getPosition();
	mMousePosition.x = sf::Mouse::getPosition().x + camera->getView()->getCenter().x;
	*/
	//float x = static_cast<float>(sf::Mouse::getPosition(*mWindow).x) / mWindow->getSize().x;
    //float y = static_cast<float>(sf::Mouse::getPosition(*mWindow).y) / mWindow->getSize().y;

	  //edge shader
	//mShader.setParameter("edge_threshold",  1 - (x + y) / 2);

	//v�g bl�r shader
	/*mShader.setParameter("wave_phase", clock.getElapsedTime().asSeconds());
    mShader.setParameter("wave_amplitude", x * 40, y * 40);
    mShader.setParameter("blur_radius", 0);
	mShader.bind(&mShader);*/
	collision();
	for(auto i:mEntities)
	{
		i->tick(mEntities[0]);
	}
	camera->tick();
	mIsEPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
}

void Game::collision()
{
	EntiyVector enteties(mEntities);
	ObjectVector objects(mMap->getObjectList());
	ObjectVector walls(mMap->getWallList());

	for (EntiyVector::size_type i = 1; i < enteties.size(); i++)
	{
		Entity *playerEntity = enteties[0];
		Entity *enemyEntity = enteties[i];
		if (overlapsEntity(playerEntity,enemyEntity) && !playerEntity->getHiding())
		{
			enteties[i] -> getFunc();
		}
		if (overlapsMouse(enemyEntity))
		{
			enteties[i] -> getFunc();
		}
	}

	for (ObjectVector::size_type i = 0; i < objects.size(); i++)
	{
		Entity *playerEntity = enteties[0];
		Object *objectEntity = objects[i];
		if (overlapsObjects(playerEntity,objectEntity))
		{
			//Visa E-symbol h�r
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !mIsEPressed)
			{
				objects[i] -> getFunc(playerEntity);
				break;
			}
		}
	}

	for (ObjectVector::size_type i = 0; i < walls.size(); i++)
	{
		Entity *playerEntity = enteties[0];
		Object *wallEntity = walls[i];
		if (overlapsObjects(playerEntity, wallEntity))
		{
			walls[i] -> getFunc(playerEntity);
		}
	}
}

void Game::loadMap(std::string filename, int mapID)
{
	delete mMap;
	while (!mEntities.empty())
	{
		delete mEntities[mEntities.size()-1];
		mEntities.pop_back();
	}
	mMap = new Map(mapID);
	mMap->setTexture(mFH->getTexture(mapID));
	mRenderTexture.create(mFH->getTexture(mapID)->getSize().x,mFH->getTexture(mapID)->getSize().y);
	std::ifstream stream;
	stream.open(filename);
	std::string output;
	std::vector<int> dataVector;
	int x, y, width, height, typeID, dialogueID, targetMapID, targetPortalID, portalID, speed, direction, patrolStart, patrolStop;
	while(!stream.eof())
	{
		stream >> output;
		dataVector.push_back(atoi(output.c_str()));
	}
	
	for (int i = 0; i < dataVector.size(); i++)
	{
		switch(dataVector[i])
		{
		case 0://Spelare
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			speed = dataVector[i + 5];
			mEntities.push_back(new Player(x, y, width, height, speed, mFH->getTexture(0), 4));
			camera->setTarget(mEntities[0]);
			i += 5;
			break;
		case 1://Fiende
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			direction = dataVector[i + 5]; //0 �r v�nster, 1 �r h�ger
			speed = dataVector[i + 6];
			patrolStart = dataVector[i + 7];
			patrolStop = dataVector[i + 8];
			typeID = dataVector[i + 9];
			mEntities.push_back(new Enemy(x, y, width, height, speed, direction, patrolStart, patrolStop, mFH->getTexture(typeID), typeID)); //skickar int men tar emot float == problem?
			i += 9; //i += x d�r 'x' �r antalet variabler
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
			portalID = dataVector[i +7];
			typeID = dataVector[i + 8];
			mMap->addPortal(new Portal(sf::FloatRect(x, y, width, height), mMap->getID(), targetMapID, targetPortalID, portalID, mFH->getTexture(typeID), typeID));
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
	mMap->setupPortals();
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
	mouseRect.setPosition(mMousePosition.x-mWindow->getSize().x/2,mMousePosition.y - mouseY);
	mouseRect.setSize(sf::Vector2f(15,15));
	mWindow -> draw(mouseRect);
}