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
		if (map->getTriggerList()[3]->getTrigged()) //Fade out f�rsta bilden
		{
			map->getTriggerList()[3]->setActive(false);
			map->getTriggerList()[4]->setActive(true);
			map->getAnimatedObjectList()[0]->fadeout();
			map->getAnimatedObjectList()[1]->fadein();
			map->getAnimatedObjectList()[3]->fadein();
		}
		if (map->getTriggerList()[4]->getTrigged()) //Fade out f�rsta bilden
		{
			map->getTriggerList()[4]->setActive(false);
			map->getTriggerList()[3]->setActive(true);
			map->getAnimatedObjectList()[0]->fadein();
			map->getAnimatedObjectList()[1]->fadeout();
			map->getAnimatedObjectList()[3]->fadeout();
		}
		break;
	case 2:
		if (map->getTriggerList()[0]->getTrigged()) //Om spelaren g�r p� keycard l�ses d�rren upp
		{
			map->getTriggerList()[0]->setActive(false);
			map->getSuperPortalList()[2]->setActive(true);
		}
		if (map->getTriggerList()[1]->getTrigged()) //Man n�r slutet av banan
		{
			map->getTriggerList()[1]->setActive(false);
			return 3;
		}
		break;
	case 3:
		//return 2;
		if (map->getTriggerList()[0]->getTrigged()) //Man g�r igenom f�rsta d�rren som l�ses och monstret spawnar
		{
			map->getTriggerList()[0]->setActive(false);
			map->getWallList()[0]->setActive(true);
			entityVector[1]->setActive(true);
			map->getAnimatedObjectList()[0]->setActive(true);
		}

		if (map->getTriggerList()[1]->getTrigged()) //Monstret l�ser upp f�rsta d�rren
		{
			map->getTriggerList()[1]->setActive(false);
			map->getWallList()[0]->setActive(false);
			map->getAnimatedObjectList()[0]->setActive(false);
		}

		if (map->getTriggerList()[2]->getTrigged()) //Monstret l�ser upp andra d�rren
		{
			map->getTriggerList()[2]->setActive(false);
			map->getWallList()[1]->setActive(false);
			map->getAnimatedObjectList()[1]->setActive(false);
		}

		if (map->getTriggerList()[3]->getTrigged()) //Man n�r slutet av banan och monstret flyttas n�rmare och springer mot slutet
		{
			map->getTriggerList()[3]->setActive(false);
			entityVector[1]->setPosition(sf::FloatRect(5800, 84, 1, 1));
			entityVector[1]->setTargetX(8000);
			bool1 = true;
		}
		
		if (bool1 == true && entityVector[0]->getActive() == false && entityVector[1]->isEating() == false) //Om monstret �ter spelaren s� f�rsvinner det
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