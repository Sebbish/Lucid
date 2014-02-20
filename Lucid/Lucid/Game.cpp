#include "Game.h"

Game::Game()
{
	angle = 0;
	mAmbientRed = 4;
	mAmbientGreen = 4;
	mAmbientBlue = 6;
	mAmbient = sf::Color(mAmbientRed,mAmbientGreen,mAmbientBlue,255);
	testLight = sf::Color(100, 100, 100, 178);
	mFH = new FilHanterare();
	mWindow.create(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	mWindow.setMouseCursorVisible(false);
	/*std::vector<sf::VideoMode, std::allocator<sf::VideoMode>> test;
	test = sf::VideoMode::getFullscreenModes();
	mWindow = new sf::RenderWindow(test[17], "Lucid", sf::Style::Fullscreen);*/
	//mWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	//mEntities.push_back(new Player(1200,875-768/3,1024/4,768/3,6,mFH->getTexture(0),4));
	mWindow.setFramerateLimit(60);
	mWindow.setVerticalSyncEnabled(true);
	lm = new db::LightManager(sf::Vector2i(10000, 10000));
	mRenderTexture.create(10000, 10000);
	mDialog = new Dialog();
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
	
	mSL = new SaveLoad();

	mMobil = new Mobil(mFH->getTexture(34),mSL,mMap->getID());
	mAmbiance = new ambiance();
}

Game::~Game()
{
}

void Game::run()
{
	lm->setAmbient(mAmbient);
	while (mWindow.isOpen())
    {
		input(mControlledEntity);
		tick();
		
		mWindow.clear(sf::Color(255, 0, 255));
		mWindow.setView(*camera->getView());
		render();
		//mousePositionFunc();
		
        mWindow.display();
    }
}

void Game::input(Entity* entity)
{
	switch (mMenu)
	{
	case false:
		{
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !mIsFPressed)//OnOff f�r ficklampa
			{
				mLights[0]->setOnOff(!mLights[0]->getOnOff());
			}
		//kollar om Q trycktes ned och mindcontrollar d�
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !mIsQPressed)
			{
				//kontrollerar om den kontrollerade entiteten �r spelaren
				if(mControlledEntity == mEntities[0])
				{
					Entity* enemie = NULL;
					//kollar alla entiteter och kollar vilken som �r n�rmast av de som �r p� samma y-level och innom 200p range
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
			if(mMobil->getSkriver())
			{
				if(event.type == sf::Event::TextEntered)
					mMobil->addTextToSaveSlot((char)event.text.unicode);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				mMobil->nextApp();
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				mMobil->lastApp();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !mIsEPressed)
			{
				if(mMobilActivateApp())
					break;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && mMobil->getSkriver())
			{
				mMobil->save(mMap->getID());
				mMobil->setWritingText(false);
				mMobil->reset();
			}
			break;
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !mIsMPressed)
	{
		if(mMobil->getActivate())
		{
			mMobil->deactivate();
			mMenu = false;
		}else
		{
			mControlledEntity->setMove(false);
			mMobil->activate(camera->getView(),mMap->getID());
			mMenu = true;
		}
	}
}

bool Game::mMobilActivateApp()
{
	if(mMobil->getActiveAppID() == 3)
		{
			mWindow.close();
		}else if(mMobil->getActiveAppID() == 4)
		{
				mMobil->deactivate();
				loadMap("../Debug/map1.txt", 1);
				return true;
		}else if(mMobil->IWantToLoad())
		{
			if(mMobil->getActiveAppID() == 7)
			{
				std::stringstream a;//g�r en typ string
				a << mSL->load(0); // g�r om int till string
				loadMap("../Debug/map"+a.str()+".txt",mSL->load(0));
				mMobil->reset();
				mMobil->deactivate();
				return true;
			}else if(mMobil->getActiveAppID() == 8)
			{
				std::stringstream a;//g�r en typ string
				a << mSL->load(1); // g�r om int till string
				loadMap("../Debug/map"+a.str()+".txt",mSL->load(1));
				mMobil->reset();
				mMobil->deactivate();
				return true;
			}else if(mMobil->getActiveAppID() == 9)
			{
				std::stringstream a;//g�r en typ string
				a << mSL->load(2); // g�r om int till string
				loadMap("../Debug/map"+a.str()+".txt",mSL->load(2));
				mMobil->reset();
				mMobil->deactivate();
				return true;
			}
		}

		return false;
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

	//Render event h�r

	for(auto i:mEntities){
		if (i -> getLayer() == Entity::Front)
			i->render(&mRenderTexture, mVisualizeValues);
	}

	mMap->renderForeground(&mRenderTexture);

	mRenderTexture.display();
	const sf::Texture& s = mRenderTexture.getTexture();
	sf::Sprite ss;
	ss.setTexture(s);
	//mWindow->draw(ss,&mShader);
	mWindow.draw(ss,&mEffects->getShader());//Sk�ter ljust styrka baserat p� om ficklampa �r p� eller ej.
	if (mLights[0]->getOnOff() == false && mAmbientBlue < 7 && mAmbientGreen < 4 && mAmbientRed < 4)
	{
		mAmbientBlue += 0.025;
		mAmbientGreen += 0.025;
		mAmbientRed += 0.05;
	}
	else if (mLights[0]->getOnOff() == true)
	{
		mAmbientBlue = 1;
		mAmbientGreen = 1;
		mAmbientRed = 2;
	}

	mAmbient = sf::Color(mAmbientRed,mAmbientGreen,mAmbientBlue,255);
	lm->setAmbient(mAmbient);
	lm->render(mWindow);
	mDialog->render(&mWindow);
	mMobil->render(&mWindow);
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
	mMobil->tick();

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

	mAmbiance->tick();

	mIsEPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
	mIsFPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
	mIsQPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
	mIsMPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::M);
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
					// Man d�r
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

	for (ObjectVector::size_type i = 0; i < objects.size(); i++) //Objekt man m�ste trycka E p�
	{
		Entity *controlledEntity = mControlledEntity;
		Object *objectEntity = objects[i];
		if (overlapsObjects(controlledEntity,objectEntity))
		{
			//Visa E-symbol h�r
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
	//mRenderTexture.create(10000, 10000);
	//mRenderTexture.create(mFH->getTexture(mapID)->getSize().x,mFH->getTexture(mapID)->getSize().y);
	std::ifstream stream;
	stream.open(filename);
	std::string output;
	std::vector<int> dataVector;
	int x, y, width, height, typeID, dialogueID, targetMapID, targetPortalID, portalID, speed, direction, patrolStart, patrolStop, active, animationPic, color, layer, onOff;
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
			mEntities.push_back(new Player(x, y, width, height, speed, mFH->getTexture(0), 8,mFH->getSound(1)));
			mControlledEntity = mEntities[0];
			camera = new Camera(sf::Vector2f(mWindow.getSize()),mControlledEntity);
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
			active = dataVector[i + 10];
			mEntities.push_back(new Enemy(x, y, width, height, speed, direction, patrolStart, patrolStop, mFH->getTexture(typeID), typeID, active, mFH->getSound(1),mFH->getSound(3))); //skickar int men tar emot float == problem?
			i += 10; //i += x d�r 'x' �r antalet variabler
			break;
		case 2://V�gg
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
			i += 7;
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
		case 8://Ljusk�lla
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			color = dataVector[i + 3];
			onOff = dataVector[i + 4];
			typeID = dataVector[i + 5];
			mLightSources.push_back(new Flashlight(x, y, testLight, onOff, mFH->getTexture(typeID)));
			i += 5;
			break;
		case 9://AnimatedObject
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			typeID = dataVector[i + 3];
			active = dataVector[i + 4];
			layer = dataVector[i + 5]; //0 == BehindObjects, 1 == InFrontOfObjects, 2 == Foreground
			mMap->addAnimatedObject(new AnimatedObject(sf::FloatRect(x, y, 0, 0), mFH->getTexture(typeID), typeID, active, layer));
			i += 5;
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