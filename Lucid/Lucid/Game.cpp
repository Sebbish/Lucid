#include "Game.h"

Game::Game()
{
	std::ifstream stream;
	stream.open("config.txt");
	std::string output;
	std::vector<int> dataVector;
	while(!stream.eof())
	{
		stream >> output;
		dataVector.push_back(atoi(output.c_str()));
	}
	stream.close();
	stream.clear();
	float tempSeen = dataVector[27];
	float tempControl = dataVector[25];
	mSanityLossWhileSeen = tempSeen / 1000;
	mSanityLossWhileControlling = tempControl / 1000;


	angle = 0;
	mAmbientRed = 0;
	mAmbientGreen = 0;
	mAmbientBlue = 0;

	mCurrentMap = 0;
	mAmbient = sf::Color(mAmbientRed,mAmbientGreen,mAmbientBlue,255);
	testLight = sf::Color(100, 100, 100, 255);
	mFH = new FilHanterare();
	mAtmospherScaleX = 1;
	mAtmospherScaleY = 1.6;
	mSanity = new Sanity(mFH->getTexture(63));
	mLightLevel = false;
	mFlashlightOnOff = false;
	mWindow.create(sf::VideoMode::getDesktopMode(), "Lucid",sf::Style::Fullscreen);
	mWindow.setMouseCursorVisible(false);
	/*std::vector<sf::VideoMode, std::allocator<sf::VideoMode>> test;
	test = sf::VideoMode::getFullscreenModes();
	mWindow = new sf::RenderWindow(test[17], "Lucid", sf::Style::Fullscreen);*/
	//mWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
	//mEntities.push_back(new Player(1200,875-768/3,1024/4,768/3,6,mFH->getTexture(0),4));
	//mWindow.setFramerateLimit(60);           
	mWindow.setVerticalSyncEnabled(true);
	lm = new db::LightManager(sf::Vector2i(mWindow.getSize().x,mWindow.getSize().y));
	mRenderTexture.create(mWindow.getSize().x, mWindow.getSize().y);
	mDialog = new Dialog(*mFH->getTexture(45));
	mSL = new SaveLoad();
	mMobil = new Mobil(mFH->getTexture(41),mFH->getTexture(42),0,mFH->getTexture(45),mWindow.getSize());
	mEButton = new Button(mFH->getTexture(53));
	mEButton->willRender(true);
	mQButton = new Button(mFH->getTexture(54));
	mQButton->willRender(false);
	mFButton = new Button(mFH->getTexture(59));
	mFButton->willRender(false);
	loadMap("map1.txt", 1);
	mMobil->setCurrentLevel(1);

	
	mFade = new Fade(mFH->getTexture(27), mRenderTexture);
	mPortalFade = new PortalFade(mFH->getTexture(27), mRenderTexture);
	mEffects = new Effects();
	mEvent = new Event();
	mVisualizeValues = false;
	mMenu = false;
	mCharFlash = false;
	mFlashOn = false;
	mFlashlighSound.setBuffer(*mFH->getSound(9));
	mFlashlighSound.setPitch(1.5f);
	mDeathSound.setBuffer(*mFH->getSound(0));
	

	//ladda shader
	//mShader.loadFromFile("P:/SFML-2.1/examples/shader/resources/edge.frag",sf::Shader::Fragment);
	//mShader.loadFromFile("P:/SFML-2.1/examples/shader/resources/wave.vert","P:/SFML-2.1/examples/shader/resources/blur.frag");
	//fixar edge shader*/
	//mShader.setParameter("texture", sf::Shader::CurrentTexture);
	
	tempTexture.create(1920, 1080);
	
	mAmbiance = new ambiance();
	mMobil->activate(&mWindow);
	mMenu = true;
}

Game::~Game()
{
}

void Game::run()
{
	sf::Font MyFont;
		if (!MyFont.loadFromFile("LucidProject/Resources/Dialog/ariblk.ttf"))
		{
			// Error...
		}

		mSanityMeter.setFont(MyFont);
		mSanityMeter.setScale(1,1);
		mSanityMeter.setOrigin(mSanityMeter.getGlobalBounds().left + mSanityMeter.getGlobalBounds().width,mSanityMeter.getGlobalBounds().top + mSanityMeter.getGlobalBounds().height);
		mSanityMeter.setPosition(mWindow.getSize().x,mWindow.getSize().y-10);
		mSanityMeter.setColor(sf::Color(128, 128, 0));
	lm->setAmbient(mAmbient);
	int temp = sf::Joystick::getButtonCount(0);
	while (mWindow.isOpen())
    {
		FPSclock.restart();
		mWindow.clear(sf::Color(0, 0, 0));
		if(mMobil->snakes)
		{
			mMobil->tick();
			mMobil->render(mWindow);
			mIsEscapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
		}
		else
		{
			input(mControlledEntity);
			tick();
		//	mWindow.setView(*camera->getView());
			render();
			//mousePositionFunc();
			mWindow.display();
			/*for(int i = 0; i < temp;i++)
				std::cout << sf::Joystick::isButtonPressed(0,i) << " " << i << std::endl;*/
			/*std::cout << sf::Joystick::isButtonPressed(0,1) << std::endl;
			system("CLS");*/
		}
		while(FPSclock.getElapsedTime().asMicroseconds() < 1000000/60)
		{}
    }
}

sf::Joystick j;

void Game::input(Entity* entity)
{
	switch (mMenu)
	{
	case false:
		{
		while (mWindow.pollEvent(event))
		{
			/*if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !mIsEscapePressed))
				mWindow.close();*/
			if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || j.getAxisPosition(0,sf::Joystick::X) >= 50) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
			{
				entity->setDirection(Entity::RIGHT);
				entity->setMove(true);
				if (mMap->getID() == 7)
				{
					if (entity == mEntities[0])
					{
						mEntities[1]->setDirection(Entity::RIGHT);
						mEntities[1]->setMove(true);
					}
					else
					{
						mEntities[0]->setDirection(Entity::RIGHT);
						mEntities[0]->setMove(true);
					}
				}
			}else if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || j.getAxisPosition(0,sf::Joystick::X) <= -50) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
			{
				entity->setDirection(Entity::LEFT);
				entity->setMove(true);
				if (mMap->getID() == 7)
				{
					if (entity == mEntities[0])
					{
						mEntities[1]->setDirection(Entity::LEFT);
						mEntities[1]->setMove(true);
					}
					else
					{
						mEntities[0]->setDirection(Entity::LEFT);
						mEntities[0]->setMove(true);
					}
				}
			}else
			{
				entity->setMove(false);
				if (mMap->getID() == 7)
				{
					if (entity == mEntities[0])
					{
						mEntities[1]->setMove(false);
					}
					else
					{
						mEntities[0]->setMove(false);
					}
				}
			}
	//Debug
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
			//{
			//	mEffects->setNextShader(0);
			//}
			//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			//{
			//	mEffects->setNextShader(1);
			//}
			//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			//{
			//	mEffects->setNextShader(2);
			//}
			//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			//{
			//	mEffects->setNextShader(3);
			//}
			//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			//{
			//	mEffects->setNextShader(4);
			//}
			//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
			//{
			//	mVisualizeValues = !mVisualizeValues;
			//}
			//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
			//{
			//		mWindow.create(sf::VideoMode::getDesktopMode(), "Lucid");
			//		mWindow.setVerticalSyncEnabled(true);
			//		mWindow.setMouseCursorVisible(false);
			//}
			//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6))
			//{
			//		mWindow.create(sf::VideoMode::getDesktopMode(), "Lucid", sf::Style::Fullscreen);
			//		mWindow.setVerticalSyncEnabled(true);
			//		mWindow.setMouseCursorVisible(false);
			//}

			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||sf::Joystick::getAxisPosition(0,sf::Joystick::V) >= 50)
			//{
			//	mEntities[0]->setMaxSpeed(24);
			//}
			//else
			//	mEntities[0]->setMaxSpeed(6);


		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Joystick::isButtonPressed(0,2)) && !mIsFPressed && mControlledEntity == mEntities[0] && mEntities[0]->getHiding() == false && mCharFlash == true)//OnOff f�r ficklampa

		{
			if (mFlashlightOnOff == true)
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
			else
			{
				mFlashlightOnOff = true;
			}
			mFlashlighSound.stop();
			mFlashlighSound.play();
		}
		//kollar om Q trycktes ned och mindcontrollar d�
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::isButtonPressed(0,1)) && !mIsQPressed && (mMap->getID() > 4 || (mMap->getID() == 4 && mMap->getTriggerList()[0]->getActive() == false))/*&& mMobil->getMC*/ )
		{
			if (mMap->getID() == 7 && mMap->getTriggerList()[0]->getActive() == false)
			{
				setControlledEntity(mEntities[1]);
			}
			else
			{
				//kontrollerar om den kontrollerade entiteten �r spelaren
				if(mControlledEntity == mEntities[0])
				{
					Entity* enemie = NULL;

					//kollar alla entiteter och kollar vilken som �r n�rmast av de som �r p� samma y-level och innom 200p range
					for(auto i:mEntities)
					{
						if(mEntities[0]->getRect().top >= i->getRect().top-100 && mEntities[0]->getRect().top <= i->getRect().top+100 && i != mEntities[0] && i->getActive())
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

				}
				else
				{
					mControlledEntity->resetTargetX();
					mControlledEntity->setWait();
					setControlledEntity(mEntities[0]);
				}
			}
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0)) && mControlledEntity != mEntities[0])
		{
			mControlledEntity->toggleRoofStance();
		}

	//Debug
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && mControlledEntity != mEntities[0])
		{
			mControlledEntity->hitRoof();
		}*/

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
		//{
		//	loadMap("../Debug/map"+std::to_string(mMap->getID() - 1)+".txt",mMap->getID() - 1);
		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
		//{
		//	loadMap("../Debug/map"+std::to_string(mMap->getID())+".txt",mMap->getID());
		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
		//{
		//	loadMap("../Debug/map"+std::to_string(mMap->getID() + 1)+".txt",mMap->getID() + 1);
		//}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		//{
		//	mMap->getTriggerList()[2]->setActive(true);
		//	mEntities[1]->setActive(false);
		//}
	}
	break;


	case true:
		{   
			sf::Joystick::update();
			if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0,sf::Joystick::Y) >= 50 || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && !mIsDownPressed)
			{
				mMobil->nextApp();
			}else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0,sf::Joystick::Y) <= -50 || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !mIsUpPressed)
			{
				mMobil->lastApp();
			}
			if((sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0,0)) && !mIsEPressed || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if(mMobilActivateApp())
					break;
			}
			break;
		}
	}


	if((sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !mIsMPressed) || ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0,3)) && !mIsEscapePressed))
	{
		if(mMobil->getActivate())
		{
			mMobil->deactivate();
			mMenu = false;
		}else
		{
			mControlledEntity->setMove(false);
			mMobil->activate(&mWindow);
			mMenu = true;
		}
	}
	
}

bool Game::mMobilActivateApp()
{
		if(mMobil->getActiveAppID() == 0)
		{
				mMobil->deactivate();
				mMenu = false;
				loadMap("../Debug/map1.txt", 1);
				mIsEPressed = true;
				return true;
		}else if(mMobil->getActiveAppID() == 1)
		{
				mMobil->deactivate();
				mMenu = false;
				loadMap("../Debug/map"+std::to_string(mSL->load(0))+".txt", mSL->load(0));
				mIsEPressed = true;
				return true;
		}else if(mMobil->getActiveAppID() == 3)
		{
			mWindow.close();
		}

		return false;
}

void Game::render()
{

	mRenderTexture.clear();
	mRenderTexture.setView(*camera->getView());
	lm->setView(*camera->getView());

	if (mMap->getID() == 2 && mEntities[0]->getRect().top == 487 && mEntities[0]->getRect().left > 4999 && mEntities[0]->getRect().left < 5689)
		mEntities[0]->render(&mRenderTexture, mVisualizeValues, true, false);
	if (mMap->getID() == 20 && mEntities[0]->getRect().top == 44 && mEntities[0]->getRect().left > 50 && mEntities[0]->getRect().left < 550)
		mEntities[0]->render(&mRenderTexture, mVisualizeValues, true, false);
	if (mMap->getID() == 12)
		mEntities[0]->render(&mRenderTexture, mVisualizeValues, true, false);

	mMap->renderMap(&mRenderTexture);
	for(auto i:mEntities)
		if (i -> getLayer() == Entity::Back)
			i->render(&mRenderTexture, mVisualizeValues, false, false);
	
	mMap -> renderObjects(&mRenderTexture);

	//Render event h�r

	for(auto i:mEntities)
		if (i -> getLayer() == Entity::Front)
		{
			if (mMap->getID() == 7 && i == mEntities[1])
				i->render(&mRenderTexture, mVisualizeValues, false, true);
			else
				i->render(&mRenderTexture, mVisualizeValues, false, false);
		}
	

	mMap->renderForeground(&mRenderTexture);


	mRenderTexture.display();
	const sf::Texture& s = mRenderTexture.getTexture();
	sf::Sprite ss;
	ss.setTexture(s);
	mWindow.draw(ss/*,&mSanity->getShader()*/);//Sk�ter ljus styrka baserat p� om ficklampa �r p� eller ej.
	
	mAmbient = sf::Color(mAmbientRed,mAmbientGreen,mAmbientBlue,255);
	lm->setAmbient(mAmbient);
	lm->render(mWindow);

	////Ritar om f�nstret med shader
	tempTexture.update(mWindow);
	sf::Sprite tempSprite;
	tempSprite.setTexture(tempTexture);
	mWindow.clear(sf::Color(0, 0, 0));
	mWindow.draw(tempSprite, &mSanity->getShader());


	mEButton->render(&mWindow, camera);
	mQButton->render(&mWindow, camera);
	mFButton->render(&mWindow, camera);
	mDialog->render(&mWindow);
	if(mMobil->getActivate())
	{
		sf::RectangleShape rss;
		rss.setPosition(mWindow.getPosition().x,mWindow.getPosition().y);
		rss.setSize(sf::Vector2f(mWindow.getSize().x,mWindow.getSize().y));
		rss.setFillColor(sf::Color(0,0,0,180));
		mWindow.draw(rss);
		mMobil->render(mWindow);
	}
	mMobil->VoiceMailRender(&mWindow);

	mSanityMeter.setString("Sanity: " + std::to_string(mSanity->getSanity()));
	mSanityMeter.setOrigin(mSanityMeter.getLocalBounds().left + mSanityMeter.getLocalBounds().width,mSanityMeter.getLocalBounds().top + mSanityMeter.getLocalBounds().height);
	mSanity->render(&mWindow);
	//mWindow.draw(mSanityMeter);
	mFade->render(mWindow);
	mPortalFade->render(mWindow);
	if(mMap->getID() == 12)
		mCred->render(mWindow);
}

void Game::tick()
{

	mEButton->setObject(0, false);
	mFButton->setObject(0, false);
	mQButton->setObject(0, true);
	mFButton->setObject(0, false);

	mEffects->tick(clock);

	int newMap = mFade->tick();
	if (newMap != 0)
	{
		mSanity->setSanity(25);
		if (mSanity->getSanity() <= 50)
		{
			mSanity->setSanity(-(mSanity->getSanity()));
			mSanity->setSanity(50);
		}
		//mFade->fadeOut(newMap);
		mMobil->setCurrentLevel(newMap);
		std::string mapName = "../Debug/map";
		mapName += std::to_string(newMap);
		mapName += ".txt";
		loadMap(mapName, newMap);
	}

	if (mEntities[0]->getActive() == false && mEntities[0]->getImortal() == false) // Om spelaren d�r.
	{
		mSanity->die();
		if (mSanity->fadeIsDone())
		{
			std::string mapName = "../Debug/map";
			mapName += std::to_string(0);
			mapName += ".txt";
			loadMap(mapName, 20);
			mSanity->live();
		}
	}

	sf::FloatRect rect = mPortalFade->tick();
	if (rect != sf::FloatRect(0, 0, 0, 0))
	{
		mControlledEntity->setPosition(rect);
		camera->setTarget(mControlledEntity);
	}


	for(auto i:mEntities)
	{
		i->tick(mEntities[0], mEntities);
	}

	
	mMap->tick();

	collision();

	//FADE H�R
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	if(mMap->getID() == 12)
		if(mCred->tick()){
			delete mCred;
			loadMap("../Debug/map2.txt", 2);
			return;
		}
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	newMap = mEvent->tick(mMap, mEntities, mLights, mMobil, mQButton, mControlledEntity, camera, mFButton,mSanity,mMap->getObjectList());


	if (newMap != 0)
	{
		if (!mSanity->getWhiteFadeOut())
		{
			mFade->fadeOut(newMap);
		}
		else
		{
			std::string mapName = "../Debug/map";
			mapName += std::to_string(newMap);
			mapName += ".txt";
			loadMap(mapName, newMap);
			mSanity->live();
		}
	}

	camera->tick();
	mDialog->tick(camera->getView());
	if(mMobil->getActivate())
		mMobil->tick();
	mMobil->VoiceMailTick();

	//Plaserar ficklampans position.
	if (mFlashlightOnOff == true && mFlashOn == true)
	{
		mLights[0]->setOnOff(true);
		mLights[2]->setOnOff(true);
	}
	else
	{
		mLights[0]->setOnOff(false);
		mLights[2]->setOnOff(false);
	}
	
	if (mEntities[0]->getDirection() == Entity::LEFT)
	{
		mLights[0]->flipSprite(0);
		mLights[0]->setPosition(sf::Vector2f(mEntities[0]->getRect().left - mLights[0]->getXSize() + 140, mEntities[0]->getRect().top));
		mLights[2]->flipSprite(0);
		mLights[2]->setPosition(sf::Vector2f(mEntities[0]->getRect().left, mEntities[0]->getRect().top));
		
	}
	else
	{
		mLights[0]->flipSprite(1);
		mLights[0]->setPosition(sf::Vector2f(mEntities[0]->getRect().left+(mEntities[0]->getRect().width) - 140, mEntities[0]->getRect().top));
		mLights[2]->flipSprite(1);
		mLights[2]->setPosition(sf::Vector2f(mEntities[0]->getRect().left, mEntities[0]->getRect().top));
	}


	if (mAmbientRed < 50 && mAmbientGreen < 50 && mAmbientBlue < 55)//Sett Player walk sprite
	{
		mCharFlash = true;
		
	}
	else
	{
		mCharFlash = false;
		mFlashlightOnOff = false;
	}
	mEntities[0]->flashlight(mCharFlash);


	if (mControlledEntity == mEntities[0]) //!!!Charlight �r 256 h�g, det blir inget ljus �ver det!!!
	{
		if ((mFlashlightOnOff == false || mFlashOn == false) && mAtmospherScaleX <= 3)
		{
			mAtmospherScaleX += 0.003;
		}
		else if (mAtmospherScaleX >= 1)
		{
			mAtmospherScaleX -= 0.06;
		}

		/*if (mAtmospherScaleY >= 1)
		{
			mAtmospherScaleY -= 0.06;
		}*/
	}
	else
	{
		if (mAtmospherScaleX <= 5)
		{
			mAtmospherScaleX += 0.006;
		}
		/*if (mFlashlightOnOff == false && mAtmospherScaleY <= 5)aad
		{
			mAtmospherScaleY += 0.003;
		}*/
	}

	if (mControlledEntity != mEntities[0] || mEntities[0]->getHiding() == true)	//St�nger av ficklampan n�r man tar kontrol eller g�mmer sig.
	{
		mFlashOn = false;	
	}
	else
	{
		mFlashOn = true;
	}
	//M�rkerseende baserat p� om man �r spelare eller monster.
	if (mControlledEntity != mEntities[0])
	{
		sf::Color ambSetColor(150,100,200,200);
		mLights[1]->setColor(ambSetColor);
	}
	else
	{
		sf::Color atmosf�r(35,35,39,255);
		mLights[1]->setColor(atmosf�r);
	}

	//�ndrar ambiencen.
	mAmbientRed = mLights[0]->getWorldLightRed();
	mAmbientGreen = mLights[0]->getWorldLightGreen();
	mAmbientBlue = mLights[0]->getWorldLightBlue();

	mLights[1]->setScale(mAtmospherScaleX,mAtmospherScaleY);
	//mLights[1]->setPosition(sf::Vector2f(mControlledEntity->getRect().left - ((512 * mAtmospherScaleX / 4) + (mAtmospherScaleX-1) * 256 / 2), mControlledEntity->getRect().top /*- ((256 * mAtmospherScaleY / 4) + (mAtmospherScaleY-1) * 256 / 2)*/));
	mLights[1]->setPosition(sf::Vector2f(mControlledEntity->getRect().left - ((512 * mAtmospherScaleX / 4) + (mAtmospherScaleX-1) * 256 / 2), camera->getView()->getCenter().y-44 - 250 /*- ((256 * mAtmospherScaleY / 4) + (mAtmospherScaleY-1) * 256 / 2)*/));

	//Sanity baserade utr�kningar
	bool tempBrus = false;
	if (mControlledEntity != mEntities[0])
	{
		if (mMap->getID() != 7)
		{
			//mSanity->setSanity(-0.021);
			mSanity->setSanity(-mSanityLossWhileControlling);
		}
		else
		{
			mSanity->setSanity(mSanityLossWhileControlling);
		}
		tempBrus = true;
	}

	for(auto i:mEntities){
			if (i->getCanSeePlayer() == true && i->getActive() == true )
			{
				//mSanity->setSanity(-0.101);
				mSanity->setSanity(-mSanityLossWhileSeen);
				tempBrus = true;
			}
			else
			{
				mSanity->setSanity(0);
			}
	}
	mSanity->setBrus(tempBrus);

	if (mSanity->getSanity() <= 100)
	{
		mSanity->setSanity(0.001);
	}
	if (mSanity->getSanity() <= 0)
	{
	//	mEntities[0]->setActive(false);
	}
	
	//mLights[0]->setMoveOnOff(mEntities[0]->getMove());
	//mLights[2]->setMoveOnOff(mEntities[0]->getMove());
	//for(auto i:mLights)
	//{
	//		i->tick();
	//}
	
	mAmbiance->tick(mSanity->getSanity());

	mIsEPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0,0);
	mIsFPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Joystick::isButtonPressed(0,2);
	mIsQPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Joystick::isButtonPressed(0,1);
	mIsMPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::M);
	mIsLeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	mIsRightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	mIsEscapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0,3);
	mIsDownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::getAxisPosition(0,sf::Joystick::Y) >= 50;
	mIsUpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::getAxisPosition(0,sf::Joystick::Y) <= -50;

	
	mLights[0]->setMoveOnOff(mEntities[0]->getMove());
	mLights[2]->setMoveOnOff(mEntities[0]->getMove());
	for(auto i:mLights)
	{
			i->tick();
	}

	mSanity->tick();

	if (mMap->getID() == 7)
	{
		if (mControlledEntity == mEntities[0])
		{
			mEntities[1]->setPosition(sf::FloatRect(mEntities[0]->getRect().left, mEntities[1]->getRect().top, 0, 0));
		}
		else
		{
			mEntities[0]->setPosition(sf::FloatRect(mEntities[1]->getRect().left, mEntities[0]->getRect().top, 0, 0));
		}
	}
}

void Game::collision()
{
	EntiyVector enteties(mEntities);
	ObjectVector objects(mMap->getObjectList());
	std::vector<Wall*> walls(mMap->getWallList());
	std::vector<Trigger*> triggers(mMap->getTriggerList());
	std::vector<Object*> roofs(mMap->getRoofList());
	std::vector<Portal*> portals(mMap->getSuperPortalList());
	std::vector<Object*> ventilations(mMap->getVentilationList());

	for (auto i:enteties)
	{
		for (auto j:enteties)
		{
			if (overlapsEntity(i,j) && i != j)
			{
				//if (i == enteties[0] && (!i->getHiding() || j->getHunting()) && j->getActive())
				if (i == enteties[0] && !i->getHiding() && j->getActive() && i->getActive() && mControlledEntity != j)
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
					if ((i == mControlledEntity && i->getTypeID() == 21 && j->getTypeID() == 22) || (j == mControlledEntity && j->getTypeID() == 21 && i->getTypeID() == 22)) //Kontrollen bryts
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
				while (overlapsObjects(j, roofEntity))
				{
					j->shortYStepBack();
				}
				roofEntity -> getFunc(j);
			}
		}

		for (ObjectVector::size_type i = 0; i < ventilations.size(); i++)
		{
			Object *ventEntity = ventilations[i];
			if (overlapsObjects(j, ventEntity))
			{
				ventEntity -> getFunc(j);
			}
		}
	}
	
	if (mControlledEntity == mEntities[0])
	{
		for (ObjectVector::size_type i = 0; i < objects.size(); i++) //Objekt man m�ste trycka E p�
		{
			Entity *controlledEntity = mControlledEntity;
			Object *objectEntity = objects[i];
			if (overlapsObjects(controlledEntity,objectEntity))
			{
				//Visa E-symbol h�r
				if (mMap->getID() == 4)
				{
					mQButton->setObject(objectEntity, true);
				}

				mEButton->setObject(objectEntity, false);
			

				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0,0)) && !mIsEPressed && !mMobil->getActivate())
			{
				objectEntity -> getFunc(mControlledEntity);
				break;

			}
			
		}
		}

		for (ObjectVector::size_type i = 0; i < portals.size(); i++) //Portaler
		{
			Entity *controlledEntity = mControlledEntity;
			Portal *portalEntity = portals[i];
			if (overlapsObjects(controlledEntity,portalEntity))
			{
				//Visa E-symbol h�r
				mEButton->setObject(portalEntity, false);
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0,0)) && !mIsEPressed && mEntities[0]->getActive() == true)
				{
					int newMap = portalEntity -> getFunc(mControlledEntity);
					if (newMap != 0 && controlledEntity == mEntities[0])
					{
						mFade->fadeOut(newMap);
						/*std::string mapName = "../Debug/map";
						mapName += std::to_string(newMap);
						mapName += ".txt";
						loadMap(mapName, newMap);*/
					}
					else
					{
						if (portalEntity->getActive())
							mPortalFade->fadeOut(portalEntity->getTargetPortal()->getRect());
					}
					break;
				}
			}
		}
	
}
	}

void Game::loadMap(std::string filename, int mapID)
{
	if(mapID == 12)
		mCred = new cred();
	delete mEvent;
	mEvent = new Event();
	if(mapID >= 2 && mapID != 20)	
		mSL->save(0,"hej",mapID);
	mEButton->setObject(0, true);
	mMobil->newMap(mapID);
	mDialog->newMap(mapID);
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
	int x, y, width, height, typeID, dialogueID, targetMapID, targetPortalID, portalID, speed, direction, patrolStart, patrolStop, active, animationPic, animationY, color, layer, onOff, alpha, useTexture, animate, loop, playerBased, blink,showE,trappa;
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
			typeID = dataVector[i + 6];
			mEntities.push_back(new Player(x, y, width, height, speed, mFH->getTexture(typeID), 8,mFH->getSound(1), typeID));
			mControlledEntity = mEntities[0];
			camera = new Camera(sf::Vector2f(mWindow.getSize()),mControlledEntity);
			i += 6;
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
			mEntities.push_back(new Enemy(x, y, width, height, speed, direction, patrolStart, patrolStop, mFH->getTexture(typeID), typeID, active, mFH->getSound(4),mFH->getSound(3),mFH->getSound(6),mFH->getSound(5))); //skickar int men tar emot float == problem?
			i += 10; //i += x d�r 'x' �r antalet variabler
			if(mapID == 8)
				camera->setTarget(mEntities[mEntities.size()-1]);
			if(mapID == 12)
				camera->setTarget(mEntities[mEntities.size()-1]);
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
			useTexture = dataVector[i + 10];
			direction = dataVector[i + 11];
			trappa = dataVector[i + 12];
			if(trappa == 1)
				mMap->addPortal(new Portal(sf::FloatRect(x, y, width, height), mMap->getID(), targetMapID, targetPortalID, portalID, mFH->getTexture(typeID), typeID, active, useTexture, direction, mFH->getSound(10)));
			else
				mMap->addPortal(new Portal(sf::FloatRect(x, y, width, height), mMap->getID(), targetMapID, targetPortalID, portalID, mFH->getTexture(typeID), typeID, active, useTexture, direction, mFH->getSound(2)));	
			i += 12;
			break;
		case 4://NPC
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			dialogueID = dataVector[i + 5];
			typeID = dataVector[i + 6];
			animationPic = dataVector[i + 7];
			showE = dataVector[i + 8];
			mMap->addNpc(new Npc(sf::FloatRect(x, y, width, height), dialogueID, mFH->getTexture(typeID), typeID,animationPic,mDialog,mEntities[0],mFH->getSound(typeID),showE));
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
		case 8://Ljusk�lla
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			color = dataVector[i + 5];
			onOff = dataVector[i + 6];
			typeID = dataVector[i + 7];
			animationPic = dataVector[i + 8];
			animationY = dataVector[i + 9];
			playerBased = dataVector[i + 10];
			blink = dataVector[i + 11];
			mLights.push_back(new db::Light(*mFH->getTexture(typeID), typeID, sf::Vector2f(x, y), width, height ,testLight,animationPic, animationY, onOff, playerBased, blink));
			i += 11;
			break;
		case 9://AnimatedObject
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			typeID = dataVector[i + 5];
			active = dataVector[i + 6];
			layer = dataVector[i + 7]; //0 == BehindBackGround, 1 == BehindObjects, 2 == InFrontOfObjects, 3 == Foreground
			animationY = dataVector[i + 8];
			animationPic = dataVector[i + 9];
			direction = dataVector[i + 10];
			alpha = dataVector[i + 11];
			animate = dataVector[i + 12];
			loop = dataVector[i + 13];
			mMap->addAnimatedObject(new AnimatedObject(sf::FloatRect(x, y, width, height), mFH->getTexture(typeID), typeID, active, layer, animationY, animationPic, direction, alpha, animate, loop));
			i += 13;
			break;
		case 10:// Tak/Golv
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			width = dataVector[i + 3];
			height = dataVector[i + 4];
			mMap->addRoof(new Roof(sf::FloatRect(x, y, width, height)));
			i += 4;
			break;
		case 11:// Map Stats
			mAmbientRed = dataVector[i + 1];
			mAmbientGreen = dataVector[i + 2];
			mAmbientBlue = dataVector[i + 3];
			mCurrentMap = dataVector[i + 4];
			i += 4;
			break;
		case 12://Ventilation
			x = dataVector[i + 1];
			y = dataVector[i + 2];
			height = dataVector[i + 3];
			mMap->addVentilation(new Ventilation(x, y, height));
			i += 3;
			break;
		}
	}

	for (LightVector::size_type i = 0; i < mLights.size(); i++)
	{
		lm->add(&*mLights[i]);
	}
	sf::Color atmosf�r(20,20,24,255);
	mLights[1]->setColor(atmosf�r);
	atmosf�r = sf::Color(70,100,70,255);
	mLights[2]->setColor(atmosf�r);
	mLights[0]->setWorldLight(mAmbientRed,mAmbientGreen,mAmbientBlue);
	mLights[1]->setScale(mAtmospherScaleX,mAtmospherScaleY);
	for(auto i:mLights)
	{
			i->setMoveOnOff(true);
	}
	mMap->setupPortals();


	//mFade->fadeIn();

	//if (mapID != 1)
	//{
	//	//tick();
	//	mWindow.setView(*camera->getView());
	//	int tempAlpha = 255;
	//	while (tempAlpha > 0)
	//	{
	//		tick();
	//		tempAlpha -= 20;
	//		if (tempAlpha < 0)
	//			tempAlpha = 0;
	//		r.setFillColor(sf::Color(255, 255, 255, tempAlpha));
	//		mWindow.clear(sf::Color(0, 0, 0));
	//		render();
	//		mWindow.draw(r);
	//		mWindow.display();
	//	}
	//}

	mMobil->newMap(mapID);
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

