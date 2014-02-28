#include "Game.h"

Game::Game()
{
	angle = 0;
	mAmbientRed = 0;
	mAmbientGreen = 0;
	mAmbientBlue = 0;
	mAmbient = sf::Color(mAmbientRed,mAmbientGreen,mAmbientBlue,255);
	testLight = sf::Color(100, 100, 100, 178);
	mFH = new FilHanterare();
	mAtmospherScaleX = 1;
	mAtmospherScaleY = 1;
	mSanity = new Sanity();
	mLightLevel = false;
	mFlashlightOnOff = false;
	mWindow.create(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	mWindow.setMouseCursorVisible(false);
	/*std::vector<sf::VideoMode, std::allocator<sf::VideoMode>> test;
	test = sf::VideoMode::getFullscreenModes();
	mWindow = new sf::RenderWindow(test[17], "Lucid", sf::Style::Fullscreen);*/
	//mWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	//mEntities.push_back(new Player(1200,875-768/3,1024/4,768/3,6,mFH->getTexture(0),4));
	//mWindow.setFramerateLimit(60);
	mWindow.setVerticalSyncEnabled(true);
	lm = new db::LightManager(sf::Vector2i(9000, 4000));
	mRenderTexture.create(9000, 4000);
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

	mMobil = new Mobil(mFH->getTexture(41),mFH->getTexture(42));
	mAmbiance = new ambiance();
}

Game::~Game()
{
}

void Game::run()
{
	sf::Font MyFont;
	if (!MyFont.loadFromFile("P:/Downloads/LucidProject/Resources/Dialog/ariblk.ttf"))
	{
		// Error...
	}
		
	//mSanityMeter.setString("Hello");
	mSanityMeter.setFont(MyFont);
	mSanityMeter.setScale(1,1);
		
	mSanityMeter.setColor(sf::Color(128, 128, 0));
	lm->setAmbient(mAmbient);
	while (mWindow.isOpen())
    {
		clock.restart();
		if(mMobil->snakes)
		{
			mMobil->tick();
			mMobil->render(mWindow);
			mIsEscapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
		}else
		{
			input(mControlledEntity);
			tick();
		
			mWindow.clear(sf::Color(0, 0, 0));
			mWindow.setView(*camera->getView());
			render();
			//mousePositionFunc();
			mSanityMeter.setString("Sanity: " + std::to_string(mSanity->getSanity()));
			mSanityMeter.setPosition(camera->getView()->getCenter().x + 500,camera->getView()->getCenter().y + 500);
			mWindow.draw(mSanityMeter);
			mWindow.display();

		}

		while(clock.getElapsedTime().asMicroseconds() < 16666)
		{}

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
			if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !mIsEscapePressed))
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
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
			{
					mWindow.create(sf::VideoMode::getDesktopMode(), "Lucid");
					mWindow.setVerticalSyncEnabled(true);
					mWindow.setMouseCursorVisible(false);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6))
			{
					mWindow.create(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
					mWindow.setVerticalSyncEnabled(true);
					mWindow.setMouseCursorVisible(false);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				mEntities[0]->setMaxSpeed(24);
			}
			else
				mEntities[0]->setMaxSpeed(6);


		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !mIsFPressed && mControlledEntity == mEntities[0] && mEntities[0]->getHiding() == false)//OnOff för ficklampa

			{
				if (mFlashlightOnOff == true)
				{
					mFlashlightOnOff = false;
				}
				else
				{
					mFlashlightOnOff = true;
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
				if(enemie != NULL && !enemie->getCanSeePlayer() && !enemie->getSearching() && enemie->getTypeID() == 21)
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mControlledEntity != mEntities[0])
		{
			mControlledEntity->toggleRoofStance();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && mControlledEntity != mEntities[0])
		{
			mControlledEntity->hitRoof();
		}
	}
	break;


	case true:
		{                                                                                                                                                                                                                                                                                                                                                            
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !mIsRightPressed)
			{
				mMobil->nextApp();
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !mIsLeftPressed)
			{
				mMobil->lastApp();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !mIsEPressed || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if(mMobilActivateApp())
					break;
			}
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !mIsEscapePressed)
	{
		mMobil->deactivate();
		mMenu = false;
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
			mMobil->activate(camera->getView());
			mMenu = true;
		}
	}
}

bool Game::mMobilActivateApp()
{
	if(mMobil->getActiveAppID() == 3)
		{
			mWindow.close();
		}else if(mMobil->getActiveAppID() == 0)
		{
				mMobil->deactivate();
				mMenu = false;
				loadMap("../Debug/map1.txt", 1);
				mIsEPressed = true;
				return true;
		}else if(mMobil->getActiveAppID() == 1)
		{
				loadMap("../Debug/map"+std::to_string(mSL->load(0))+".txt",mSL->load(0));
				mMobil->reset();
				mMobil->deactivate();
				mEntities[0]->setMove(false);
				mMenu = false;
				mIsEPressed = true;
				return true;
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

	//Render event här

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
	mWindow.draw(ss,&mEffects->getShader());//Sköter ljust styrka baserat på om ficklampa är på eller ej.
	/*else
	{
<<<<<<< HEAD
		mAmbientRed = 200;
		mAmbientGreen = 200;
		mAmbientBlue = 205;
	
=======
		mAmbientBlue += 0.025;
		mAmbientGreen += 0.025;
		mAmbientRed += 0.05;
	}
	else if (mLights[0]->getOnOff() == true)
	{
		mAmbientBlue = 200;
		mAmbientGreen = 200;
		mAmbientRed = 200;
	}
>>>>>>> 44b07b43702e926e10bb17ddab5df80af631b139}*/

	mAmbient = sf::Color(mAmbientRed,mAmbientGreen,mAmbientBlue,255);
	lm->setAmbient(mAmbient);
	//lm->render(mWindow);
	mDialog->render(&mWindow);
	if(mMobil->getActivate())
		mMobil->render(mWindow);
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
	if(mMobil->getActivate())
		mMobil->tick();
	mLights[0]->setOnOff(mFlashlightOnOff);

	if (mEntities[0]->getDirection() == Entity::LEFT)
	{
		mLights[0]->flipSprite(0);
		mLights[0]->setPosition(sf::Vector2f(mEntities[0]->getRect().left - mLights[0]->getXSize() + 145, mEntities[0]->getRect().top));
		
	}
	else
	{
		mLights[0]->flipSprite(1);
		mLights[0]->setPosition(sf::Vector2f(mEntities[0]->getRect().left+(mEntities[0]->getRect().width) - 145, mEntities[0]->getRect().top));
	}
	if (mFlashlightOnOff == false && mAtmospherScaleX <= 3)
	{
		mAtmospherScaleX += 0.003;
	}
	else if (mFlashlightOnOff == true && mAtmospherScaleX >= 1)
	{
		mAtmospherScaleX -= 0.06;
	}
	if (mControlledEntity != mEntities[0] || mEntities[0]->getHiding() == true)
	{
		if (mFlashlightOnOff == true)//Stänger av ficklampan när man tar kontrol.
		{
			mFlashlightOnOff = false;
		}
	}
	mLights[1]->setScale(mAtmospherScaleX,mAtmospherScaleY);
	mLights[1]->setPosition(sf::Vector2f(mControlledEntity->getRect().left - ((512 * mAtmospherScaleX / 4) + (mAtmospherScaleX-1) * 256 / 2), mControlledEntity->getRect().top));

	if (mControlledEntity != mEntities[0])
	{
		mSanity->setSanity(-0.002);
	}
	for(auto i:mEntities){
			if (i->getCanSeePlayer() == true)
			{
				mSanity->setSanity(-0.01);
			}
	}
	for(auto i:mLights)
	{
		i->tick();

	}
	mAmbiance->tick();

	mIsEPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
	mIsFPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
	mIsQPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
	mIsMPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::M);
	mIsLeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	mIsRightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	mIsEscapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

void Game::collision()
{
	EntiyVector enteties(mEntities);
	ObjectVector objects(mMap->getObjectList());
	std::vector<Wall*> walls(mMap->getWallList());
	std::vector<Trigger*> triggers(mMap->getTriggerList());
	std::vector<Object*> roofs(mMap->getRoofList());

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

		for (ObjectVector::size_type i = 0; i < roofs.size(); i++)
		{
			Object *roofEntity = roofs[i];
			if (overlapsObjects(j, roofEntity))
			{
				roofEntity -> getFunc(j);
				while (overlapsObjects(j, roofEntity))
				{
					j->shortYStepBack();
				}
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
	sf::RectangleShape r;
	r.setTexture(mFH->getTexture(27));
	r.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	r.setPosition(0, 0);
	r.setSize(sf::Vector2f(mRenderTexture.getSize().x, mRenderTexture.getSize().y));
	if (mapID != 1)
	{
		int tempAlpha = 0;
		while (tempAlpha < 255)
		{
			tempAlpha += 20;
			if (tempAlpha > 255)
				tempAlpha = 255;
			r.setFillColor(sf::Color(255, 255, 255, tempAlpha));
			mWindow.clear(sf::Color(0, 0, 0));
			render();
			mWindow.draw(r);
			mWindow.display();
		}
	}

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
	int x, y, width, height, typeID, dialogueID, targetMapID, targetPortalID, portalID, speed, direction, patrolStart, patrolStop, active, animationPic, animationY, color, layer, onOff, alpha, useTexture;
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
			useTexture = dataVector[i + 10];
			mMap->addPortal(new Portal(sf::FloatRect(x, y, width, height), mMap->getID(), targetMapID, targetPortalID, portalID, mFH->getTexture(typeID), typeID, active, useTexture, mFH->getSound(2)));
			i += 10;
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
		case 8://Ljuskälla
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			color = dataVector[i + 3];
			onOff = dataVector[i + 4];
			typeID = dataVector[i + 5];
			animationPic = dataVector[i + 6];
			mLightSources.push_back(new Flashlight(x, y, testLight, onOff, mFH->getTexture(typeID), animationPic));
			i += 6;
			break;
		case 9://AnimatedObject
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			typeID = dataVector[i + 5];
			active = dataVector[i + 6];
			layer = dataVector[i + 7]; //0 == BehindObjects, 1 == InFrontOfObjects, 2 == Foreground
			animationY = dataVector[i + 8];
			animationPic = dataVector[i + 9];
			direction = dataVector[i + 10];
			alpha = dataVector[i + 11];
			mMap->addAnimatedObject(new AnimatedObject(sf::FloatRect(x, y, width, height), mFH->getTexture(typeID), typeID, active, layer, animationY, animationPic, direction, alpha));
			i += 11;
			break;
		case 10:// Tak/Golv
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			mMap->addRoof(new Roof(sf::FloatRect(x, y, width, height)));
			i += 4;
			break;
		}
	}
	mMap->setupPortals();
	addLights();

	if (mapID != 1)
	{
		tick();
		mWindow.setView(*camera->getView());
		int tempAlpha = 255;
		while (tempAlpha > 0)
		{
			tempAlpha -= 20;
			if (tempAlpha < 0)
				tempAlpha = 0;
			r.setFillColor(sf::Color(255, 255, 255, tempAlpha));
			mWindow.clear(sf::Color(0, 0, 0));
			render();
			mWindow.draw(r);
			mWindow.display();
		}
	}
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
	sf::FloatRect playerPosition = playerEntity ->getHitBox();
	sf::FloatRect otherPosition = otherEntity ->getHitBox();
	if (playerPosition.intersects(otherPosition))
		return true;
	else
		return false;
}

bool Game::overlapsObjects(Entity *playerEntity, Object *objectEntity)
{
	sf::FloatRect playerPosition = playerEntity ->getHitBox();
	sf::FloatRect otherPosition = objectEntity ->getHitBox();
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
	sf::FloatRect otherPosition = entity ->getHitBox();
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
	sf::Color atmosfär(20,20,24,255);
	mLights[1]->setColor(atmosfär);
	mLights[0]->setScale(1,1);
	mLights[1]->setScale(mAtmospherScaleX,mAtmospherScaleY);
}