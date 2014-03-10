#ifndef SNAKE_H
#define SNAKE_H
#include "Cube.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SFML\Audio.hpp"

#include <iostream>

class snake
{
public:
	snake(sf::FloatRect &rect, bool cheat);
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
	bool frontSnakeCollideWithFruit();
	bool snakeCollideWithSnake();

	sf::Event mEvent;
	std::vector<Cube*> cubes;
	sf::Clock mClock;
	Cube* mFruit;
	int mTime;
	STATE mState;
	sf::FloatRect mRect;
	bool mRender;

	sf::Texture mSnakeTexture,mLewisTexture;
	sf::Music mMusic;
	sf::Vertex mBorder[8];
	int mScore;

	sf::Font mFont;
	sf::Text mText;

	int autoTick;
	bool start;
	bool mCheat;
	int lap;
	int animationX;
};
#endif;
