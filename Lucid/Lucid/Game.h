#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

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
};

#endif