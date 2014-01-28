#ifndef ENTITY_H
#define ENTITY_H
#include "SFML\Graphics.hpp"
class Entity
{
public:
	virtual ~Entity() = 0;
	virtual sf::Vector2f getVector()const = 0;
	virtual void setVector(sf::Vector2f) = 0; 
	virtual void setSpeed(int speed) = 0;
	virtual int getSpeed()const = 0;
	virtual void setLastSeen(sf::Vector2f) = 0;
	virtual sf::Vector2f getLastSeen()const = 0;
	virtual sf::Texture* getTexture()const = 0;
	virtual void setTexture(sf::Texture) = 0;
	virtual void tick() = 0;
	virtual void render() = 0;
};
#endif

