#include "Game.h"

Game::Game()
{
	angle = 0;
	mFH = new FilHanterare();
	mWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	//mEntities.push_back(new Player(1200,875-768/3,1024/4,768/3,6,mFH->getTexture(0),4));
	mWindow->setFramerateLimit(60);
	mWindow->setVerticalSyncEnabled(true);
	loadMap("../Debug/map1.txt", 1);
	mEffects = new Effects();
	

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
	/*sf::SoundBuffer mSound;
	mSound.loadFromFile("P:/Downloads/LucidProject/Resources/Sound/a.wav");
	sf::Sound sound;
	sound.setBuffer(mSound);
	sound.setLoop(true);
	sound.play();*/

	while (mWindow->isOpen())
    {
		input(mControlledEntity);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			mEffects->setNextShader(0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			mEffects->setNextShader(1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			mEffects->setNextShader(2);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			mEffects->setNextShader(3);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			mEffects->setNextShader(4);
		}
    }
	//kollar om Q trycktes ned och mindcontrollar då
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !mIsQPressed)
		{
			//kontrollerar om den kontrollerade entiteten är spelaren
			if(mControlledEntity == mEntities[0])
			{
				Entity* enemie = NULL;
				//kollar alla entiteter och kollar vilken som är närmast av de som är på samma y-level och innom 200p range
				for(auto i:mEntities)
				{
					if(mEntities[0]->getRect().top >= i->getRect().top-100 && mEntities[0]->getRect().top <= i->getRect().top+100 && i != mEntities[0])
					{
						if(mEntities[0]->getRect().left+mEntities[0]->getRect().width >= i->getRect().left-200 && mEntities[0]->getRect().left <= i->getRect().left+i->getRect().width+200)
						{
						if(enemie == NULL)
							enemie = i;
						else
						{
							if(mEntities[0]->getRect().left-i->getRect().left <= mEntities[0]->getRect().left-enemie->getRect().left)
								enemie = i;
						}
					}
					}
				}
				if(enemie != NULL && !enemie->getCanSeePlayer() && !enemie->getHunting() && enemie->getTypeID() == 21)
				{
					mControlledEntity->setMove(false);
					setControlledEntity(enemie);
				}

			}else
			{
				mControlledEntity->resetTargetX();
				mControlledEntity->setWait();
				setControlledEntity(mEntities[0]);
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
	//mWindow->draw(ss,&mShader);
	mWindow->draw(ss,&mEffects->getShader());
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

	//våg blör shader
	/*mShader.setParameter("wave_phase", clock.getElapsedTime().asSeconds());
    mShader.setParameter("wave_amplitude", x * 40, y * 40);
    mShader.setParameter("blur_radius", 0);
	mShader.bind(&mShader);*/

	mEffects->tick(clock);

	collision();
	for(auto i:mEntities)
	{
		i->tick(mEntities[0], mEntities);
	}
	camera->tick();
	mIsEPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
	mIsQPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
}

void Game::collision()
{
	EntiyVector enteties(mEntities);
	ObjectVector objects(mMap->getObjectList());
	ObjectVector walls(mMap->getWallList());

	for (auto i:enteties)
	{
		for (auto j:enteties)
		{
			if (overlapsEntity(i,j) && i != j)
			{
				if (i == enteties[0] && (!i->getHiding() || j->getHunting()))
				{
					// Man dör
				}
				else if (j != enteties[0] && i != enteties[0]) // 2 monster kolliderar
				{
					i ->getFunc(j);
					if (i == mControlledEntity || j == mControlledEntity) //Kontrollen bryts
					{
						setControlledEntity(enteties[0]);
					}
				}
			}
			/*if (overlapsMouse(enemyEntity))
			{
				enteties[i] -> getFunc();
			}*/
		}
	}

	for (auto j:enteties)
	{
		for (ObjectVector::size_type i = 0; i < walls.size(); i++)
		{
			Object *wallEntity = walls[i];
			if (overlapsObjects(j, wallEntity))
			{
				walls[i] -> getFunc(j);
			}
		}
	}

	for (ObjectVector::size_type i = 0; i < objects.size(); i++)
	{
		Entity *controlledEntity = mControlledEntity;
		Object *objectEntity = objects[i];
		if (overlapsObjects(controlledEntity,objectEntity))
		{
			//Visa E-symbol här
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !mIsEPressed)
			{
				int newMap = objects[i] -> getFunc(mControlledEntity);
				if (newMap != 0 && controlledEntity == mEntities[0])
				{
					std::string mapName = "../Debug/map";
					mapName += std::to_string(newMap);
					mapName += ".txt";
					loadMap(mapName, newMap);
				}
				break;
			}
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
	delete camera;
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
	stream.close();
	stream.clear();
	
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
			mControlledEntity = mEntities[0];
			camera = new Camera(sf::Vector2f(mWindow->getSize()),mControlledEntity);
			i += 5;
			break;
		case 1://Fiende
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			direction = dataVector[i + 5]; //0 är vänster, 1 är höger
			speed = dataVector[i + 6];
			patrolStart = dataVector[i + 7];
			patrolStop = dataVector[i + 8];
			typeID = dataVector[i + 9];
			mEntities.push_back(new Enemy(x, y, width, height, speed, direction, patrolStart, patrolStop, mFH->getTexture(typeID), typeID)); //skickar int men tar emot float == problem?
			i += 9; //i += x där 'x' är antalet variabler
			break;
		case 2://Vägg
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

void Game::setControlledEntity(Entity* entity)
{
	mControlledEntity->controlled(false);
	mControlledEntity = entity;
	camera->setTarget(mControlledEntity);
	mControlledEntity->controlled(true);
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