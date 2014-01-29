#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
//<<<<<<< HEAD
#include "Enemy.h"
//=======
#include "Camera.h"
//>>>>>>> 2cd13a0520ef6ff83e7006916eb7f32d1f9fe3ad

typedef std::vector<Entity*> EntiyVector;

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
	static bool overlaps(Entity *playerEntity, Entity *otherEntity);
	sf::RenderWindow *mWindow;
	EntiyVector mEntities;
	Camera *camera;
};

#endif