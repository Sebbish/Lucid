#ifndef OBJECT_H
#define OBJECT_H

#include <SFML\Graphics.hpp>

class Object
{
public:
	virtual ~Object() = 0;
	virtual sf::Vector2f getPosition()const = 0;
	virtual sf::Vector2f getSize()const = 0;
};

#endif
