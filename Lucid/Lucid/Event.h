#ifndef EVENT_H
#define EVENT_H
#include "Map.h"
#include "Enemy.h"
#include "Light.h"
#include "Button.h"
#include "Mobil.h"

class Event
{
public:
	Event(void);
	~Event(void);
	int tick(Map* map, std::vector<Entity*> &entityVector, std::vector<db::Light*> LightVector, Mobil *mMobil, Button* QButton, Entity* &controlledEntity, Camera* camera);
private:
	bool bool1, bool2, bool3;
	sf::Clock mClock;
	int timer;
};

#endif