#ifndef HIDING_H
#define HIDING_H

#include "object.h"

class Hiding :
	public Object
{
public:
	Hiding(sf::Vector2f position, sf::Vector2f size);
	~Hiding();
	virtual sf::Vector2f getPosition()const;
	virtual sf::Vector2f getSize()const;
private:
	sf::Vector2f mPosition;
	sf::Vector2f mSize;
};

#endif
