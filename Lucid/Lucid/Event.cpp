#include "Event.h"

Event::Event(void)
{
	bool1 = false;
	bool2 = false;
	bool3 = false;
}

Event::~Event(void)
{
}

int Event::tick(Map* map, std::vector<Entity*> &entityVector, std::vector<db::Light*> LightVector)
{
	std::vector<Trigger*> triggers = map->getTriggerList();
	std::vector<AnimatedObject*> animatedObjects = map->getAnimatedObjectList();
	std::vector<Wall*> walls = map->getWallList();
	std::vector<Portal*> portals = map->getSuperPortalList();

	switch (map->getID())
	{
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
			animatedObjects[3]->fadein();
		}
		if (map->getTriggerList()[3]->getTrigged()) //Fade out andra bilden
		{
			triggers[3]->setActive(false);
			triggers[2]->setActive(true);
			animatedObjects[0]->fadein();
			animatedObjects[1]->fadeout();
			animatedObjects[3]->fadeout();
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
			
			animatedObjects[2]->setActive(false);
			triggers[13]->setActive(true);
			LightVector[0]->setWorldLight(0,0,0);
		}

		if (map->getTriggerList()[13]->getTrigged()) //Då spelaren använder keycard på kortläsaren.
		{
			map->getTriggerList()[13]->setActive(false);
			portals[14]->setActive(true);
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
		}

		if (triggers[2]->getTrigged()) //Monstret låser upp andra dörren
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

		if (mClock.getElapsedTime().asMilliseconds() > timer && bool2)
		{
			walls[1]->setActive(false);
			animatedObjects[1]->setActive(false);
			bool2 = false;
		}

		if (triggers[3]->getTrigged()) //Man når slutet av banan och monstret flyttas närmare och springer mot slutet
		{
			triggers[3]->setActive(false);
			entityVector[1]->setPosition(sf::FloatRect(5800, 44, 1, 1));
			entityVector[1]->setTargetX(8000);
			entityVector[0]->setImortal(true);
			bool1 = true;
		}
		
		if (bool1 == true && entityVector[0]->getActive() == false && entityVector[1]->isEating() == false) //Om monstret äter spelaren så försvinner det
		{
			bool1 = false;
			entityVector[1]->setActive(false);
			entityVector[0]->setActive(true);
			entityVector[0]->setImortal(false);
			map->getSuperPortalList()[0]->setActive(true);
		}
		break;





	case 4:
		if (triggers[0]->getTrigged()) //Monstret spawnar
		{
			triggers[0]->setActive(false);
			entityVector[1]->setActive(true);
			entityVector[1]->setForm(Entity::ROOFTRAVEL, Entity::ROOF, true);
			entityVector[1]->setPosition(sf::FloatRect(6666, 0, 256, 256));
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
			bool1 = true;
		}

		if (mClock.getElapsedTime().asMilliseconds() > timer && bool1)
		{
			walls[0]->setActive(false);
			animatedObjects[0]->setActive(false);
			bool1 = false;
		}
		break;
	}
	return 0;
}