#ifndef SNAKE_H
#define SNAKE_H
#include "Cube.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

class snake
{
public:
	snake(sf::FloatRect &rect);
	~snake();
	bool exitPls()const;
	bool gameOVER()const;
	void exit();
	void tick();
	bool getRender()const;
	void setRender(bool render);
	void render(sf::RenderWindow& target);
private:
	enum STATE
	{
	GAME,
	OVER,
	EXIT
	};
	void init();
	void spawnNewFruit();
	void collide();
	bool snakeCollideWithFruit();
	bool snakeCollideWithSnake();

	sf::Event mEvent;
	std::vector<Cube*> cubes;
	sf::Clock mClock;
	Cube* mFruit;
	int mTime;
	STATE mState;
	sf::FloatRect mRect;
	bool mRender;

	sf::Texture t,l;
	
	int mScore;

	sf::Font mFont;
	sf::Text mText;
};
#endif;
