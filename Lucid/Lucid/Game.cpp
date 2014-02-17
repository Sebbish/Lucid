#include "Game.h"

Game::Game()
{
	angle = 0;
	mAmbientRed = 0;
	mAmbientGreen = 4;
	mAmbientBlue = 6;
	testLight = sf::Color(255, 255, 255, 178);
	mFH = new FilHanterare();
	mWindow.create(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	/*std::vector<sf::VideoMode, std::allocator<sf::VideoMode>> test;
	test = sf::VideoMode::getFullscreenModes();
	mWindow = new sf::RenderWindow(test[17], "Lucid", sf::Style::Fullscreen);*/
	//mWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	//mEntities.push_back(new Player(1200,875-768/3,1024/4,768/3,6,mFH->getTexture(0),4));
	mWindow.setFramerateLimit(60);
	mWindow.setVerticalSyncEnabled(true);
	lm = new db::LightManager(sf::Vector2i(10000, 10000));
	loadMap("../Debug/map1.txt", 1);
	mEffects = new Effects();
	mEvent = new Event();
	mVisualizeValues = false;
	mMenu = false;

	mDeathSound.setBuffer(*mFH->getSound(0));
	//ladda shader
	//mShader.loadFromFile("P:/SFML-2.1/examples/shader/resources/edge.frag",sf::Shader::Fragment);
	//mShader.loadFromFile("P:/SFML-2.1/examples/shader/resources/wave.vert","P:/SFML-2.1/examples/shader/resources/blur.frag");

	//fixar edge shader*/
	//mShader.setParameter("texture", sf::Shader::CurrentTexture);
	mDialog = new Dialog();
	mSL = new SaveLoad();
}

Game::~Game()
{
}

void Game::run()
{
	sf::Color ambient(255, 255, 255, 255);
	lm->setAmbient(ambient);
	while (mWindow.isOpen())
    {
		input(mControlledEntity);
		tick();
		
		mWindow.clear(sf::Color(255, 0, 255));
		mWindow.setView(*camera->getView());
		render();
		//mousePositionFunc();
		lm->render(mWindow);
        mWindow.display();
    }
}

void Game::input(Entity* entity)
{
	switch (mMenu)
	{
	case false:
		{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				mWindow.close();
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
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
			{
				mVisualizeValues = !mVisualizeValues;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				mEntities[0]->setMaxSpeed(24);
			}
			else
				mEntities[0]->setMaxSpeed(6);
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
		break;


	case true:
		{
			break;
		}
	}
}



void Game::render()
{
	mRenderTexture.clear();
	mMap->renderMap(&mRenderTexture);
	for(auto i:mEntities){
		if (i -> getLayer() == Entity::Back)
			i->render(&mRenderTexture, mVisualizeValues);
	}
	mMap -> renderObjects(&mRenderTexture);

	//Render event här

	for(auto i:mEntities){
		if (i -> getLayer() == Entity::Front)
			i->render(&mRenderTexture, mVisualizeValues);
	}
	mRenderTexture.display();
	mDialog->render(&mRenderTexture);
	const sf::Texture& s = mRenderTexture.getTexture();
	sf::Sprite ss;
	ss.setTexture(s);
	//mWindow->draw(ss,&mShader);
	mWindow.draw(ss,&mEffects->getShader());
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
	mMap->tick();
	//collision();
	/*bool canSee = false;*/
	for(auto i:mEntities)
	{
		i->tick(mEntities[0], mEntities);
		/*if (i->getCanSeePlayer() || i->getHunting())
		{
			canSee = true;
		}*/
	}
	/*if (canSee)
	{
		mEffects->setNextShader(3);
		camera->zoom(true);
	}
	else
	{
		mEffects->setNextShader(1);
		camera->zoom(false);
	}*/
	collision();

	int newMap = mEvent->tick(mMap, mEntities);
	if (newMap != 0)
	{
		std::string mapName = "../Debug/map";
					mapName += std::to_string(newMap);
					mapName += ".txt";
					loadMap(mapName, newMap);
	}

	camera->tick();
	mDialog->tick(camera->getView());

	if (mEntities[0]->getDirection() == Entity::LEFT)
	{
		mLights[0]->flipSprite(0);
		mLights[0]->setPosition(sf::Vector2f(mEntities[0]->getRect().left, mEntities[0]->getRect().top));
	}
	else
	{
		mLights[0]->flipSprite(1);
		mLights[0]->setPosition(sf::Vector2f(mEntities[0]->getRect().left+(mEntities[0]->getRect().width), mEntities[0]->getRect().top));
	}


	mIsEPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
	mIsQPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
}

void Game::collision()
{
	EntiyVector enteties(mEntities);
	ObjectVector objects(mMap->getObjectList());
	std::vector<Wall*> walls(mMap->getWallList());
	std::vector<Trigger*> triggers(mMap->getTriggerList());

	for (auto i:enteties)
	{
		for (auto j:enteties)
		{
			if (overlapsEntity(i,j) && i != j)
			{
				//if (i == enteties[0] && (!i->getHiding() || j->getHunting()) && j->getActive())
				if (i == enteties[0] && !i->getHiding() && j->getActive() && i->getActive())
				{
					// Man dör
					j->getFunc(i);
					mEntities[0]->setActive(false);
					if(mDeathSound.getStatus() != sf::Sound::Playing)
						mDeathSound.play();
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
				wallEntity -> getFunc(j);
			}
		}

		for (ObjectVector::size_type i = 0; i < triggers.size(); i++)
		{
			Object *triggerEntity = triggers[i];
			if (overlapsObjects(j, triggerEntity))
			{
				triggerEntity -> getFunc(j);
			}
		}
	}

	for (ObjectVector::size_type i = 0; i < objects.size(); i++) //Objekt man måste trycka E på
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
	
	for (LightVector::size_type i = 0; i < mLights.size(); i++)
	{
		lm->remove(&*mLights[i]);
	}
	while (!mLights.empty())
	{
		delete mLights[mLights.size()-1];
		mLights.pop_back();
	}
	while (!mLightSources.empty())
	{
		delete mLightSources[mLightSources.size()-1];
		mLightSources.pop_back();
	}

	while (!mEntities.empty())
	{
		delete mEntities[mEntities.size()-1];
		mEntities.pop_back();
	}
	delete camera;
	mMap = new Map(mapID);
	mMap->setTexture(mFH->getTexture(mapID));
	mRenderTexture.create(10000, 10000);
	//mRenderTexture.create(mFH->getTexture(mapID)->getSize().x,mFH->getTexture(mapID)->getSize().y);
	std::ifstream stream;
	stream.open(filename);
	std::string output;
	std::vector<int> dataVector;
	int x, y, width, height, typeID, dialogueID, targetMapID, targetPortalID, portalID, speed, direction, patrolStart, patrolStop, active, animationPic, color;
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
			mEntities.push_back(new Player(x, y, width, height, speed, mFH->getTexture(0), 4,mFH->getSound(1)));
			mControlledEntity = mEntities[0];
			camera = new Camera(sf::Vector2f(mWindow.getSize()),mControlledEntity);
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
			active = dataVector[i + 10];
			mEntities.push_back(new Enemy(x, y, width, height, speed, direction, patrolStart, patrolStop, mFH->getTexture(typeID), typeID, active, mFH->getSound(1),mFH->getSound(3))); //skickar int men tar emot float == problem?
			i += 10; //i += x där 'x' är antalet variabler
			break;
		case 2://Vägg
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			active = dataVector[i + 5]; //0 == false
			mMap->addWall(new Wall(sf::FloatRect(x, y, width, height), active));
			i += 5;
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
			active = dataVector[i + 9];
			mMap->addPortal(new Portal(sf::FloatRect(x, y, width, height), mMap->getID(), targetMapID, targetPortalID, portalID, mFH->getTexture(typeID), typeID, active, mFH->getSound(2)));
			i += 9;
			break;
		case 4://NPC
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			dialogueID = dataVector[i + 5];
			typeID = dataVector[i + 6];
			animationPic = dataVector[i + 7];
			mMap->addNpc(new Npc(sf::FloatRect(x, y, width, height), dialogueID, mFH->getTexture(typeID), typeID,animationPic,mDialog,mEntities[0]));
			i += 8;
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
		case 6://Trigger
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			active = dataVector[i + 5]; //0 == false
			typeID = dataVector[i + 6]; //TriggedByID
			mMap->addTrigger(new Trigger(sf::FloatRect(x, y, width, height), typeID, active));
			i += 6;
			break;
		case 7://Parallax
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			typeID = dataVector[i + 3];
			mMap->addParallax(new Parallax(sf::FloatRect(x, y, 0, 0), mFH->getTexture(typeID), typeID, camera));
			i += 3;
			break;
		case 8:
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			color = dataVector[i + 3];
			typeID = dataVector[i + 4];
			mLightSources.push_back(new Flashlight(x, y, testLight, mFH->getTexture(typeID)));
			i += 4;
			break;
		}
	}
	mMap->setupPortals();
	addLights();
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
	mouseRect.setPosition(mMousePosition.x-mWindow.getSize().x/2,mMousePosition.y - mouseY);
	mouseRect.setSize(sf::Vector2f(15,15));
	mWindow.draw(mouseRect);
}

void Game::addLights()
{
	for (auto i:mLightSources)
	{
		mLights.push_back(i->render());
	}
	for (LightVector::size_type i = 0; i < mLights.size(); i++)
	{
		lm->add(&*mLights[i]);
	}
}