#ifndef ENTITY_H
#define ENTITY_H
#include "SFML\Graphics.hpp"

class Entity
{
public:
	enum direction {
		LEFT,
		RIGHT
	};
	virtual ~Entity() = 0;
	virtual sf::FloatRect getRect()const = 0;
	virtual void getFunc() = 0;
	virtual void setDirection(direction d) = 0;
	virtual direction getDirection()const = 0;
	virtual void setRect(sf::FloatRect rect) = 0;
	virtual void setMove(bool move) = 0;
	virtual bool getMove()const = 0;
	virtual void setMaxSpeed(float speed) = 0;
	virtual float getMaxSpeed()const = 0;
	virtual void setLastSeen(sf::Vector2f lastSeen) = 0;
	virtual sf::Vector2f getLastSeen()const = 0;
	virtual sf::Texture* getTexture()const = 0;
	virtual void setTexture(sf::Texture* texture) = 0;
	virtual void tick(Entity *player) = 0;
	virtual void render(sf::RenderWindow* window) = 0;
};
#endif

