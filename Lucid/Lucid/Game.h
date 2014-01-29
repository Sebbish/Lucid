#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Object.h"
//<<<<<<< HEAD
#include "Enemy.h"
//=======
#include "Camera.h"
//>>>>>>> 2cd13a0520ef6ff83e7006916eb7f32d1f9fe3ad
#include "FilHanterare.h"
#include "Map.h"

typedef std::vector<Entity*> EntiyVector;
typedef std::vector<Object*> ObjectVector;

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	void tick();
	void render();
	void collision();
	static bool overlapsEntity(Entity *playerEntity, Entity *otherEntity);
	static bool overlapsObjects(Entity *playerEntity, Object *objectEntity);
	static bool overlapsMouse(Entity *entity);
	void mousePositionFunc();
	sf::RenderWindow *mWindow;
	sf::Vector2i mMousePosition;
	EntiyVector mEntities;
	ObjectVector mObjects;
	Camera *camera;
	FilHanterare* mFH;
	Map *map;
};

#endif