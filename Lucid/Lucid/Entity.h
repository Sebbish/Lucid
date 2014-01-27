#ifndef ENTITY_H
#define ENTITY_H
#include "SFML\Graphics.hpp"
class Entity
{
public:
	virtual ~Entity() = 0;
	virtual sf::Vector2f getVector()const = 0;
	virtual void setVector(sf::Vector2f) = 0; 
};
#endif

