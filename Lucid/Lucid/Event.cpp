#include "Event.h"

Event::Event(void)
{
	bool1 = false;
}

Event::~Event(void)
{
}

int Event::tick(Map* map, std::vector<Entity*> &entityVector)
{
	switch (map->getID())
	{
	case 1:
		if (map->getTriggerList()[0]->getTrigged()) //Byter bana
		{
			map->getTriggerList()[0]->setActive(false);
			map->getAnimatedObjectList()[4]->setAnimate(true);
		}
		if (map->getTriggerList()[1]->getTrigged()) //Byter bana
		{
			map->getTriggerList()[1]->setActive(false);
			map->getAnimatedObjectList()[5]->setAnimate(true);
		}
		if (map->getTriggerList()[2]->getTrigged()) //Byter bana
		{
			map->getTriggerList()[2]->setActive(false);
			return 2;
		}
		if (map->getTriggerList()[3]->getTrigged()) //Fade out första bilden
		{
			map->getTriggerList()[3]->setActive(false);
			map->getTriggerList()[4]->setActive(true);
			map->getAnimatedObjectList()[0]->fadeout();
			map->getAnimatedObjectList()[1]->fadein();
			map->getAnimatedObjectList()[3]->fadein();
		}
		if (map->getTriggerList()[4]->getTrigged()) //Fade out första bilden
		{
			map->getTriggerList()[4]->setActive(false);
			map->getTriggerList()[3]->setActive(true);
			map->getAnimatedObjectList()[0]->fadein();
			map->getAnimatedObjectList()[1]->fadeout();
			map->getAnimatedObjectList()[3]->fadeout();
		}
		break;
	case 2:
		if (map->getTriggerList()[0]->getTrigged()) //Om spelaren går på keycard låses dörren upp
		{
			map->getTriggerList()[0]->setActive(false);
			map->getSuperPortalList()[2]->setActive(true);
		}
		if (map->getTriggerList()[1]->getTrigged()) //Man når slutet av banan
		{
			map->getTriggerList()[1]->setActive(false);
			return 3;
		}
		break;
	case 3:
		//return 2;
		if (map->getTriggerList()[0]->getTrigged()) //Man går igenom första dörren som låses och monstret spawnar
		{
			map->getTriggerList()[0]->setActive(false);
			map->getWallList()[0]->setActive(true);
			entityVector[1]->setActive(true);
			map->getAnimatedObjectList()[0]->setActive(true);
		}

		if (map->getTriggerList()[1]->getTrigged()) //Monstret låser upp första dörren
		{
			map->getTriggerList()[1]->setActive(false);
			map->getWallList()[0]->setActive(false);
			map->getAnimatedObjectList()[0]->setActive(false);
		}

		if (map->getTriggerList()[2]->getTrigged()) //Monstret låser upp andra dörren
		{
			map->getTriggerList()[2]->setActive(false);
			map->getWallList()[1]->setActive(false);
			map->getAnimatedObjectList()[1]->setActive(false);
		}

		if (map->getTriggerList()[3]->getTrigged()) //Man når slutet av banan och monstret flyttas närmare och springer mot slutet
		{
			map->getTriggerList()[3]->setActive(false);
			entityVector[1]->setPosition(sf::FloatRect(5800, 84, 1, 1));
			entityVector[1]->setTargetX(8000);
			bool1 = true;
		}
		
		if (bool1 == true && entityVector[0]->getActive() == false && entityVector[1]->isEating() == false) //Om monstret äter spelaren så försvinner det
		{
			bool1 = false;
			entityVector[1]->setActive(false);
			entityVector[0]->setActive(true);
			map->getSuperPortalList()[0]->setActive(true);
		}
		break;
	}
	return 0;
}