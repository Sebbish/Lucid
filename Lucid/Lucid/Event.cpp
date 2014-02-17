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
		if (map->getTriggerList()[0]->getTrigged())
		{
			map->getTriggerList()[0]->setActive(false);
			map->getSuperPortalList()[2]->setActive(true);
		}
		if (map->getTriggerList()[1]->getTrigged())
		{
			map->getTriggerList()[1]->setActive(false);
			return 2;
		}
		break;
	case 2:
		if (map->getTriggerList()[0]->getTrigged())
		{
			map->getTriggerList()[0]->setActive(false);
			map->getWallList()[0]->setActive(true);
			entityVector[1]->setActive(true);
		}

		if (map->getTriggerList()[1]->getTrigged())
		{
			map->getTriggerList()[1]->setActive(false);
			map->getWallList()[0]->setActive(false);
		}

		if (map->getTriggerList()[2]->getTrigged())
		{
			map->getTriggerList()[2]->setActive(false);
			map->getWallList()[1]->setActive(false);
		}

		if (map->getTriggerList()[3]->getTrigged())
		{
			map->getTriggerList()[3]->setActive(false);
			entityVector[1]->setPosition(sf::FloatRect(5800, 84, 1, 1));
			entityVector[1]->setTargetX(8000);
			bool1 = true;
		}
		
		if (bool1 == true && entityVector[0]->getActive() == false && entityVector[1]->isEating() == false)
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