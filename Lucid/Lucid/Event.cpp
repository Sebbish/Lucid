#include "Event.h"

Event::Event(void)
{
	bool1 = false;
}

Event::~Event(void)
{
}

int Event::tick(Map* map, std::vector<Entity*> &entityVector, std::vector<db::Light*> LightVector)
{
	std::vector<Trigger*> triggers = map->getTriggerList();
	std::vector<AnimatedObject*> animatedObjects = map->getAnimatedObjectList();
	std::vector<Wall*> walls = map->getWallList();

	switch (map->getID())
	{
	case 1:
		if (triggers[0]->getTrigged()) //�ppnar d�rren
		{
			triggers[0]->setActive(false);
			animatedObjects[4]->setAnimate(true);
		}
		if (triggers[1]->getTrigged()) //�ppnar hissen
		{
			triggers[1]->setActive(false);
			animatedObjects[5]->setAnimate(true);
		}
		if (triggers[2]->getTrigged()) //Byter bana
		{
			triggers[2]->setActive(false);
			return 2;
		}
		if (triggers[3]->getTrigged()) //Fade out f�rsta bilden
		{
			triggers[3]->setActive(false);
			triggers[4]->setActive(true);
			animatedObjects[0]->fadeout();
			animatedObjects[1]->fadein();
			animatedObjects[3]->fadein();
		}
		if (map->getTriggerList()[4]->getTrigged()) //Fade out andra bilden
		{
			triggers[4]->setActive(false);
			triggers[3]->setActive(true);
			animatedObjects[0]->fadein();
			animatedObjects[1]->fadeout();
			animatedObjects[3]->fadeout();
		}
		break;
	case 2:
		if (triggers[0]->getTrigged()) //Om spelaren g�r p� keycard
		{
			map->getTriggerList()[0]->setActive(false);
			map->getAnimatedObjectList()[1]->setActive(false);
			map->getTriggerList()[1]->setActive(true);
			LightVector[0]->setWorldLight(0,0,0);
			
		}
		if (map->getTriggerList()[1]->getTrigged()) //D� spelaren anv�nder keycard p� kortl�saren.
		{
			map->getTriggerList()[1]->setActive(false);
			map->getSuperPortalList()[2]->setActive(true);
		}
		if (map->getTriggerList()[2]->getTrigged()) //Man n�r slutet av bannan
		{
			map->getTriggerList()[2]->setActive(false);
			return 3;
		}
		break;
	case 3:
		//return 2;
		if (triggers[0]->getTrigged()) //Man g�r igenom f�rsta d�rren som l�ses och monstret spawnar
		{
			triggers[0]->setActive(false);
			walls[0]->setActive(true);
			entityVector[1]->setActive(true);
			animatedObjects[0]->setActive(true);
		}

		if (triggers[1]->getTrigged()) //Monstret l�ser upp f�rsta d�rren
		{
			triggers[1]->setActive(false);
			walls[0]->setActive(false);
			animatedObjects[0]->setActive(false);
		}

		if (triggers[2]->getTrigged()) //Monstret l�ser upp andra d�rren
		{
			triggers[2]->setActive(false);
			walls[1]->setActive(false);
			animatedObjects[1]->setActive(false);
		}

		if (triggers[3]->getTrigged()) //Man n�r slutet av banan och monstret flyttas n�rmare och springer mot slutet
		{
			triggers[3]->setActive(false);
			entityVector[1]->setPosition(sf::FloatRect(5800, 44, 1, 1));
			entityVector[1]->setTargetX(8000);
			entityVector[0]->setImortal(true);
			bool1 = true;
		}
		
		if (bool1 == true && entityVector[0]->getActive() == false && entityVector[1]->isEating() == false) //Om monstret �ter spelaren s� f�rsvinner det
		{
			bool1 = false;
			entityVector[1]->setActive(false);
			entityVector[0]->setActive(true);
			entityVector[0]->setImortal(false);
			map->getSuperPortalList()[0]->setActive(true);
		}
		break;
	case 4:
		if (triggers[0]->getTrigged()) //Man g�r igenom f�rsta d�rren som l�ses och monstret spawnar
		{
			triggers[0]->setActive(false);
			entityVector[1]->setActive(true);
			entityVector[1]->setForm(Entity::ROOFTRAVEL, Entity::ROOF, true);
			entityVector[1]->setPosition(sf::FloatRect(6666, 0, 256, 256));
		}
		break;
	}
	return 0;
}