#ifndef EVENT_H
#define EVENT_H
#include "Map.h"
#include "Enemy.h"
#include "Light.h"
class Event
{
public:
	Event(void);
	~Event(void);
	int tick(Map* map, std::vector<Entity*> &entityVector, std::vector<db::Light*> LightVector);
private:
	bool bool1;
};

#endif