#ifndef EVENT_H
#define EVENT_H
#include "Map.h"
#include "Enemy.h"
class Event
{
public:
	Event(void);
	~Event(void);
	int tick(Map* map, std::vector<Entity*> &entityVector);
private:
	bool bool1, bool2, bool3;
	sf::Clock mClock;
	int timer;
};

#endif