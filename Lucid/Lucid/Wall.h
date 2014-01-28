#ifndef WALL_H
#define WALL_H

#include "object.h"

class Wall :
	public Object
{
public:
	Wall(sf::Vector2f position, sf::Vector2f size);
	~Wall();
	virtual sf::Vector2f getPosition()const;
	virtual sf::Vector2f getSize()const;
private:
	sf::Vector2f mPosition;
	sf::Vector2f mSize;
};

#endif