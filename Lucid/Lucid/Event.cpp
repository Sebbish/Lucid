#include "Event.h"

Event::Event(void)
{
	bool1 = false;
	bool2 = false;
	bool3 = false;
	bool4 = false;

	tick1 = 0;
	tick1Speed = 0.3;
}

Event::~Event(void)
{
}

int Event::tick(Map* map, std::vector<Entity*> &entityVector, std::vector<db::Light*> LightVector, Mobil *mMobil, Button* QButton, Entity* &controlledEntity, Camera* camera, Button* FButton,Sanity* mSanity,std::vector<Object*> &object)
{
	std::vector<Trigger*> triggers = map->getTriggerList();
	std::vector<AnimatedObject*> animatedObjects = map->getAnimatedObjectList();
	std::vector<Wall*> walls = map->getWallList();
	std::vector<Portal*> portals = map->getSuperPortalList();


	switch (map->getID())
		
	{
	case 20:
		if (triggers[0]->getTrigged())
		{	
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				return mMobil->getCurrentLevel();
			}
		}
		break;
	case 1:
		if (triggers[0]->getTrigged()) //Öppnar dörren
		{
			triggers[0]->setActive(false);
			animatedObjects[4]->setAnimate(true);
		}
		if (triggers[1]->getTrigged()) //Öppnar hissen
		{
			triggers[1]->setActive(false);
			animatedObjects[5]->setAnimate(true);
		}
		if (triggers[2]->getTrigged()) //Fade out första bilden
		{
			triggers[2]->setActive(false);
			triggers[3]->setActive(true);
			animatedObjects[0]->fadeout();
			animatedObjects[1]->fadein();
			animatedObjects[9]->fadein();
		}
		if (map->getTriggerList()[3]->getTrigged()) //Fade out andra bilden
		{
			triggers[3]->setActive(false);
			triggers[2]->setActive(true);
			animatedObjects[0]->fadein();
			animatedObjects[1]->fadeout();
			animatedObjects[9]->fadeout();
		}
		break;




	case 2:
		for (int i = 0; i <= 5; i++)//Utanför rummen
		{
			if (triggers[i]->getTrigged())
			{
				for (int j = 0; j <= 5; j++)
				{
					triggers[j]->setActive(true);
				}
				triggers[i]->setActive(false);
			}
		}

		for (int i = 6; i <= 11; i++)//I rummen
		{
			if (triggers[i]->getTrigged())
			{
				for (int j = 0; j <= 5; j++)
				{
					if (!triggers[j]->getActive())
					{
						portals[j]->setTargetPortal(portals[i]);
						portals[i]->setTargetPortal(portals[j]);

						for (int k = 0; k <= 5; k++)
						{
							if (k != j && portals[k]->getTargetPortal()->getPortalID() == portals[i]->getPortalID())
								portals[k]->setTargetPortal(portals[i+1]);
						}
					}
				}
				triggers[i]->setActive(false);
			}
		}

		if (triggers[12]->getTrigged()) //Om spelaren går på keycard
		{
			triggers[12]->setActive(false);
			triggers[16]->setActive(true);
			animatedObjects[2]->setActive(false);
			triggers[13]->setActive(true);
			LightVector[0]->setWorldLight(0,0,0);
			for (int i = 3; i <= 26; i++)
			{
				if (i == 6 || i == 9 || i == 13 || i == 21 || i == 25)
				{
					LightVector[i]->setBlink(true);
				}
				else
				{
					LightVector[i]->setOnOff(false);
				}
				
			}

			for (int i = 7; i <= 29; i++)
			{
				animatedObjects[i]->scale(192);
				animatedObjects[i]->setActive(true);
			}
			

			mMobil->nextSound();
		}

		if (map->getTriggerList()[13]->getTrigged()) //Då spelaren använder keycard på kortläsaren.
		{
			map->getTriggerList()[13]->setActive(false);
			animatedObjects[3]->setAnimate(true);
			portals[14]->setActive(true);
		}

		if (map->getTriggerList()[14]->getTrigged())
		{
			animatedObjects[4]->setActive(true);
			animatedObjects[5]->setActive(false);
		}

		if (map->getTriggerList()[15]->getTrigged())
		{
			animatedObjects[5]->setActive(true);
			animatedObjects[4]->setActive(false);
		}

		if (map->getTriggerList()[16]->getTrigged())
		{
			FButton->willRender(true);
			FButton->setObject(animatedObjects[2], false);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				triggers[16]->setActive(false);
				FButton->willRender(false);
			}
		}

		if (triggers[17]->getTrigged()) //Öppnar hissen
		{
			triggers[16]->setActive(false);
			animatedObjects[6]->setAnimate(true);
		}
		break;





	case 3:
		//return 2;
		if (triggers[0]->getTrigged()) //Man går igenom första dörren som låses och monstret spawnar
		{
			triggers[0]->setActive(false);
			walls[0]->setActive(true);
			entityVector[1]->setActive(true);
			animatedObjects[0]->setActive(true);
			mMobil->nextSound();

			//dörren
			animatedObjects[3]->setActive(true);
			animatedObjects[4]->setActive(false);
		}

		if (triggers[1]->getTrigged()) //Monstret låser upp första dörren
		{
			triggers[1]->setActive(false);
			if (entityVector[1]->getForm() == Entity::SLIME)
			{
				timer = 1000;
			}
			else
			{
				timer = 500;
			}
			entityVector[1]->setForm(Entity::NONE, Entity::EAT, false);
			mClock.restart();
			bool3 = true;
		}

		if (mClock.getElapsedTime().asMilliseconds() > timer && bool3)
		{
			walls[0]->setActive(false);
			animatedObjects[0]->setActive(false);
			bool3 = false;

			//dörren
			animatedObjects[4]->setActive(true);
			animatedObjects[3]->setActive(false);
		}

		if (triggers[2]->getTrigged()) //Monstret låser upp andra dörren
		{
			if (entityVector[1]->getNextForm() != Entity::ROOF && entityVector[1]->getForm() != Entity::ROOFCHANGINGBACK)
			{
				triggers[2]->setActive(false);
				if (entityVector[1]->getForm() == Entity::SLIME)
				{
					timer = 1000;
				}
				else
				{
					timer = 500;
				}
				entityVector[1]->setForm(Entity::NONE, Entity::EAT, false);
				mClock.restart();
				bool2 = true;
			}	
			else if (entityVector[1]->getForm() == Entity::ROOF)
			{
				entityVector[1]->toggleRoofStance();
			}
		}

		if (mClock.getElapsedTime().asMilliseconds() > timer && bool2)
		{
			walls[1]->setActive(false);
			animatedObjects[1]->setActive(false);
			bool2 = false;

			//dörren
			animatedObjects[5]->setActive(false);
			animatedObjects[6]->setActive(true);
		}

		if (triggers[3]->getTrigged()) //Man når slutet av banan och monstret flyttas närmare och springer mot slutet
		{
			triggers[3]->setActive(false);
			entityVector[1]->setPosition(sf::FloatRect(5800, 44, 1, 1));
			entityVector[1]->setTargetX(8000);
			entityVector[0]->setImortal(true);
			bool1 = true;
			mMobil->nextSound();
		}
		
		if (bool1 == true && entityVector[0]->getActive() == false/* && entityVector[1]->isEating() == false*/) //Om monstret äter spelaren så försvinner det
		{
			mSanity->die();
			bool1 = false;
			bool4 = true;
			/*entityVector[1]->setActive(false);
			entityVector[0]->setActive(true);
			entityVector[0]->setImortal(false);
			map->getSuperPortalList()[0]->setActive(true);*/
			mMobil->nextSound();//?
		}
		if (mSanity->fadeIsDone() && bool4)
		{
			entityVector[0]->setActive(true);
			entityVector[0]->setImortal(false);
			bool4 = false;
			return 13;
		}
		break;





	case 4:
		if (triggers[0]->getTrigged()) //Monstret spawnar
		{
			triggers[0]->setActive(false);
			entityVector[1]->setActive(true);
			entityVector[1]->setForm(Entity::ROOFTRAVEL, Entity::ROOF, true);
			entityVector[1]->setPosition(sf::FloatRect(6550, 44, 256, 256));
			bool2 = true;
			mMobil->nextSound();
			mMobil->getMC = true;
		}

		if (triggers[1]->getTrigged()) //Monstret låser upp dörren
		{
			if (entityVector[1]->getNextForm() != Entity::ROOF)
			{
				triggers[1]->setActive(false);
				if (entityVector[1]->getForm() == Entity::SLIME)
				{
					timer = 1000;
				}
				else
				{
					timer = 500;
				}
				entityVector[1]->setForm(Entity::NONE, Entity::EAT, false);
				mClock.restart();
				bool1 = true;
				mMobil->nextSound();
			}
			else if (entityVector[1]->getForm() == Entity::ROOF)
			{
				entityVector[1]->toggleRoofStance();
			}
		}
		if(triggers[2]->getTrigged()) // når slutet av banan
		{
			triggers[2]->setActive(false);
			return 5;
			//mMobil->slutPåTest = true;
		}

		if (mClock.getElapsedTime().asMilliseconds() > timer && bool1)
		{
			walls[0]->setActive(false);
			animatedObjects[0]->setActive(false);
			bool1 = false;
			bool3 = true;

			//dörren
			animatedObjects[2]->setActive(false);
			animatedObjects[3]->setActive(true);

			//Tappar kontrollen
			controlledEntity->controlled(false);
			controlledEntity = entityVector[0];
			camera->setTarget(controlledEntity);
			controlledEntity->controlled(true);
		}
		if (bool3 == true)
		{
			entityVector[1]->setTargetX(100000);
		}

		if (controlledEntity == entityVector[1] && !bool4)
		{
			bool4 = true;
		}

		if (bool2 && !bool4 && entityVector[0]->getHiding() == true)
		{
			QButton->willRender(true);
		}
		else
		{
			QButton->willRender(false);
		}

		if (triggers[3]->getTrigged())
		{
			triggers[3]->setActive(false);
			triggers[4]->setActive(true);
			animatedObjects[4]->setActive(false);
			animatedObjects[5]->setActive(true);
		}

		if (triggers[4]->getTrigged())
		{
			triggers[4]->setActive(false);
			triggers[3]->setActive(true);
			animatedObjects[5]->setActive(false);
			animatedObjects[4]->setActive(true);
		}
		break;
	case 5:
		if (triggers[0]->getTrigged()) //Om bub går på keycard
		{
			triggers[0]->setActive(false);
			
			animatedObjects[0]->setActive(false);
			triggers[1]->setActive(true);
			mSanity->setSanity(50);
		}
		if (!triggers[0]->getActive() && triggers[1]->getActive() && controlledEntity == entityVector[0])
		{
			triggers[0]->setActive(true);
			triggers[1]->setActive(false);
			animatedObjects[0]->setActive(true);
		}

		if (triggers[1]->getActive()) //Triggern har spelarens rektangel
		{
			triggers[1]->setRect(entityVector[0]->getRect());
		}

		if (triggers[1]->getTrigged()) //Bub lämnar keycard till spelaren
		{
			triggers[1]->setActive(false);
			triggers[2]->setActive(true);

			//Tappar kontrollen
			controlledEntity->controlled(false);
			controlledEntity->setActive(false);
			controlledEntity = entityVector[0];
			camera->setTarget(controlledEntity);
			controlledEntity->controlled(true);

		}
		if (controlledEntity->getTypeID() == 21)
		{
			animatedObjects[3]->setActive(false);
		}
		else
		{
			animatedObjects[3]->setActive(true);
		}

		if (triggers[2]->getTrigged()) //Spelaren går på kortläsaren
		{
			triggers[2]->setActive(false);
			animatedObjects[1]->setAnimate(true);
			walls[1]->setActive(false);
			animatedObjects[2]->setActive(false);
		}

		if (triggers[3]->getTrigged())
		{
			entityVector[1]->setTargetX(5000);
			triggers[3]->setActive(false);
			entityVector[1]->setActive(true);
			entityVector[1]->setPosition(sf::FloatRect(2772, 944, 256, 256));
		}
		if (!triggers[3]->getActive())
		{
			entityVector[2]->setTargetX(0);
		}
		break;
	

	case 6:
		if (triggers[0]->getTrigged())
		{
			triggers[0]->setActive(false);
			animatedObjects[0]->setActive(false);
			animatedObjects[1]->setActive(true);
			for (int i = 2; i <= 23; i++)
			{
				animatedObjects[i]->scale(256);
				animatedObjects[i]->setActive(true);
			}
			bool1 = true;
			bool2 = true;
		}

		if (bool1)
		{
			for (int i = 2; i <= 23; i++)
			{
				animatedObjects[i]->scale(-0.5f);
			}
		}

		if (animatedObjects[2]->getScalePixels() <= 128 && bool2)
		{
			mSanity->die();
			bool2 = false;
		}
		if (mSanity->fadeIsDone())
		{
			mSanity->live();
			for (int i = 2; i <= 23; i++)
			{
				animatedObjects[i]->setActive(false);
			}
			animatedObjects[0]->setActive(true);
			animatedObjects[1]->setActive(false);
			bool1 = false;
		}

		if (triggers[1]->getTrigged())
		{
			triggers[1]->setActive(false);
			return 7;
		}

		if (triggers[2]->getTrigged() && controlledEntity == entityVector[0])//BlackScreen
		{
			triggers[2]->setActive(false);
			triggers[3]->setActive(true);
			triggers[4]->setActive(true);
			triggers[5]->setActive(true);
			triggers[6]->setActive(true);

			animatedObjects[24]->setActive(false);
			animatedObjects[25]->setActive(true);
			animatedObjects[26]->setActive(true);
		}
		if (triggers[3]->getTrigged() && controlledEntity == entityVector[0])//BlackScreen
		{
			triggers[2]->setActive(true);
			triggers[3]->setActive(false);
			triggers[4]->setActive(true);
			triggers[5]->setActive(true);
			triggers[6]->setActive(true);

			animatedObjects[24]->setActive(true);
			animatedObjects[25]->setActive(false);
			animatedObjects[26]->setActive(true);
		}
		if (triggers[4]->getTrigged() && controlledEntity == entityVector[0])//BlackScreen
		{
			triggers[2]->setActive(true);
			triggers[3]->setActive(true);
			triggers[4]->setActive(false);
			triggers[5]->setActive(true);
			triggers[6]->setActive(true);

			animatedObjects[24]->setActive(true);
			animatedObjects[25]->setActive(true);
			animatedObjects[26]->setActive(false);
		}
		if (triggers[5]->getTrigged() && controlledEntity == entityVector[1])//BlackScreen
		{
			triggers[2]->setActive(true);
			triggers[3]->setActive(true);
			triggers[4]->setActive(true);
			triggers[5]->setActive(false);
			triggers[6]->setActive(true);

			animatedObjects[24]->setActive(true);
			animatedObjects[25]->setActive(false);
			animatedObjects[26]->setActive(true);
		}
		if (triggers[6]->getTrigged() && controlledEntity == entityVector[1])//BlackScreen
		{
			triggers[2]->setActive(true);
			triggers[3]->setActive(true);
			triggers[4]->setActive(true);
			triggers[5]->setActive(true);
			triggers[6]->setActive(false);

			animatedObjects[24]->setActive(true);
			animatedObjects[25]->setActive(true);
			animatedObjects[26]->setActive(false);
		}

		break;

	case 7:
		if (triggers[0]->getTrigged())
		{
			triggers[0]->setActive(false);
			entityVector[2]->setActive(true);
		}

		if (controlledEntity == entityVector[1] && !bool1)
		{
			bool1 = true;
			entityVector[2]->setIdle();
			if (entityVector[0]->getHiding())
				entityVector[0]->toggleHiding();
			walls[1]->setActive(false);
		}

		if (triggers[1]->getTrigged())
		{
			triggers[1]->setActive(false);
		}

		if (triggers[1]->getActive() == false)
		{
			tick1 += tick1Speed;
			entityVector[0]->setPosition(sf::FloatRect(entityVector[0]->getRect().left, entityVector[0]->getRect().top + tick1, 0, 0));
		}

		if (triggers[2]->getTrigged())
		{
			triggers[2]->setActive(false);
			return 15;
		}

		/*if (triggers[0]->getActive() == false)
		{
			entityVector[2]->setTargetX(1967);
		}*/

		break;


	case 8:

		if (triggers[0]->getTrigged())
		{
			triggers[0]->setActive(false);
			return 9;
		}

		break;

	case 9:
		if (triggers[0]->getTrigged()) //Öppnar dörren
		{
			triggers[0]->setActive(false);
			animatedObjects[4]->setAnimate(true);
		}
		if (triggers[1]->getTrigged()) //Öppnar hissen
		{
			triggers[1]->setActive(false);
			animatedObjects[5]->setAnimate(true);
		}
		if (triggers[2]->getTrigged()) //Fade out första bilden
		{
			triggers[2]->setActive(false);
			triggers[3]->setActive(true);
			animatedObjects[0]->fadeout();
			animatedObjects[1]->fadein();
			animatedObjects[9]->fadein();
		}
		if (map->getTriggerList()[3]->getTrigged()) //Fade out andra bilden
		{
			triggers[3]->setActive(false);
			triggers[2]->setActive(true);
			animatedObjects[0]->fadein();
			animatedObjects[1]->fadeout();
			animatedObjects[9]->fadeout();
		}
		break;




	case 10:
		if (triggers[0]->getTrigged())
		{
			triggers[0]->setActive(false);
			return 11;
		}
		break;



	case 11:
		if (triggers[0]->getTrigged())
		{
			triggers[0]->setActive(false);
			entityVector[0]->setDirection(Entity::LEFT);
		}
		break;


	case 13:
		if(triggers[0]->getTrigged())
		{
			triggers[0]->setActive(false);
			mMobil->boatLvl8Thing();
		}
		if(mMobil->playingLvl8Thing())
			triggers[1]->setActive(true);
		if(triggers[1]->getTrigged())
		{
			triggers[1]->setActive(false);
			return 4;
		}
		break;

	case 14:
		if(triggers[0]->getTrigged())
		{
			if(mMobil->getDialogID() == 10)
			{
				triggers[0]->setActive(false);
				triggers[7]->setActive(true);
			}
			entityVector[0]->setPosition(sf::FloatRect(6677,0,256,256));
			camera->moveCameraPosition(sf::Vector2f(-1937-103,0));
		}
		if(triggers[1]->getTrigged())
		{
			triggers[1]->setActive(false);
			mMobil->nextDialog();
		}
		if(triggers[2]->getTrigged())
		{
			triggers[2]->setActive(false);
			mMobil->nextDialog();
		}
		if(triggers[3]->getTrigged())
		{
			triggers[3]->setActive(false);
			mMobil->nextDialog();
		}
		if(triggers[4]->getTrigged())
		{
			triggers[4]->setActive(false);
			mMobil->nextDialog();
		}
		if(triggers[5]->getTrigged())
		{
			triggers[5]->setActive(false);
			mMobil->nextDialog();
		}
		if(triggers[6]->getTrigged())
		{
			triggers[6]->setActive(false);
			mMobil->nextDialog();
		}
		if(triggers[7]->getTrigged())
		{
			triggers[7]->setActive(false);
			return 6;
		}

		if(triggers[8]->getTrigged())
		{
			triggers[8]->setActive(false);
			object[0]->getFunc(controlledEntity);
		}
		if(triggers[9]->getTrigged())
		{
			triggers[9]->setActive(false);
			object[1]->getFunc(controlledEntity);
		}
		if(triggers[10]->getTrigged())
		{
			triggers[10]->setActive(false);
			object[2]->getFunc(controlledEntity);
		}
		if(triggers[11]->getTrigged())
		{
			triggers[11]->setActive(false);
			object[3]->getFunc(controlledEntity);
		}
		if(triggers[12]->getTrigged())
		{
			triggers[12]->setActive(false);
			object[4]->getFunc(controlledEntity);
		}
		if(triggers[13]->getTrigged())
		{
			triggers[13]->setActive(false);
			object[5]->getFunc(controlledEntity);
		}
		if(triggers[14]->getTrigged())
		{
			triggers[14]->setActive(false);
			object[6]->getFunc(controlledEntity);
		}
		if(triggers[15]->getTrigged())
		{
			triggers[15]->setActive(false);
			object[7]->getFunc(controlledEntity);
		}
		if(triggers[16]->getTrigged())
		{
			triggers[16]->setActive(false);
			object[8]->getFunc(controlledEntity);
		}
		if(triggers[17]->getTrigged())
		{
			triggers[17]->setActive(false);
			object[9]->getFunc(controlledEntity);
		}
		if(triggers[18]->getTrigged())
		{
			triggers[18]->setActive(false);
			object[10]->getFunc(controlledEntity);
		}
		if(triggers[19]->getTrigged())
		{
			triggers[19]->setActive(false);
			object[11]->getFunc(controlledEntity);
		}
		if(triggers[20]->getTrigged())
		{
			triggers[20]->setActive(false);
			object[12]->getFunc(controlledEntity);
		}
		if(triggers[21]->getTrigged())
		{
			triggers[21]->setActive(false);
			object[13]->getFunc(controlledEntity);
		}
		if(triggers[22]->getTrigged())
		{
			triggers[22]->setActive(false);
			object[14]->getFunc(controlledEntity);
		}
		break;




		case 15:
		if (triggers[0]->getTrigged())
		{
			triggers[0]->setActive(false);
			return 16;
		}



		case 16:
		if (triggers[0]->getTrigged())
		{
			triggers[0]->setActive(false);
			return 8;
		}
		break;
		}
	return 0;
}