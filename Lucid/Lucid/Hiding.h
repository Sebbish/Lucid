#ifndef HIDING_H
#define HIDING_H

#include "object.h"

class Hiding :
	public Object
{
public:
	Hiding(sf::FloatRect rect);
	~Hiding();
	virtual sf::FloatRect getRect()const;
	virtual void tick();
	virtual void render(sf::RenderWindow* window);
	virtual void getFunc();
private:
	sf::FloatRect mRect;
};

#endif
