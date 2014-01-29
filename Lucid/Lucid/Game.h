#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Object.h"
#include "Enemy.h"
#include "Camera.h"
<<<<<<< HEAD
=======
#include <fstream>
#include <string>
>>>>>>> edc2334d7a7ab2c4819ecdf436c744be4627b5ae
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
	void loadMap(std::string filename, int mapID);
	static bool overlapsEntity(Entity *playerEntity, Entity *otherEntity);
	static bool overlapsObjects(Entity *playerEntity, Object *objectEntity);
	static bool overlapsMouse(Entity *entity);
	void mousePositionFunc();
	sf::RenderWindow *mWindow;
	sf::Vector2i mMousePosition;
	EntiyVector mEntities;
	ObjectVector mObjects;
	Camera *camera;
	Map* mMap;
	FilHanterare* mFH;
};

#endif