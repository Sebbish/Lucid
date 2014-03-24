#ifndef OBJECT_H
#define OBJECT_H

#include <SFML\Graphics.hpp>
#include "Entity.h"

class Object
{
public:
	virtual ~Object() = 0;
	virtual sf::FloatRect getRect()const = 0;
	virtual sf::FloatRect getHitBox()const = 0;
	virtual bool getShowE() = 0;
	virtual int getFunc(Entity* player) = 0;
	virtual void tick() = 0;
	virtual void render(sf::RenderTexture* window) = 0;
};

#endif