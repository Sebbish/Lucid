#ifndef OBJECT_H
#define OBJECT_H

#include <SFML\Graphics.hpp>

class Object
{
public:
	virtual ~Object() = 0;
	virtual sf::FloatRect getRect()const = 0;
	virtual void tick() = 0;
	virtual void render(sf::RenderWindow* window) = 0;
};

#endif