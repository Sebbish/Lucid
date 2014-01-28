#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Camera.h"

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
	sf::RenderWindow *mWindow;
	EntiyVector mEntities;
	Camera *camera;
};

#endif