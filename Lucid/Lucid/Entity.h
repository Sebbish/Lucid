#ifndef ENTITY_H
#define ENTITY_H
#include "SFML\Graphics.hpp"



class Entity
{
public:
	virtual ~Entity() = 0;
	virtual sf::Vector2f getPosition()const = 0;
	virtual void setPosition(sf::Vector2f position) = 0;
	virtual sf::Vector2f getSize()const = 0;
	virtual void setSize(sf::Vector2f size) = 0;
	virtual void setSpeed(float speed) = 0;
	virtual float getSpeed()const = 0;
	virtual void setLastSeen(sf::Vector2f lastSeen) = 0;
	virtual sf::Vector2f getLastSeen()const = 0;
	virtual sf::Texture* getTexture()const = 0;
	virtual void setTexture(sf::Texture* texture) = 0;
	virtual void tick() = 0;
	virtual void render() = 0;
};
#endif

