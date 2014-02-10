#ifndef ENTITY_H
#define ENTITY_H
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

class Entity
{
public:
	enum direction {
		LEFT,
		RIGHT
	};
	enum layer
	{
		Front,
		Back
	};
	virtual ~Entity() = 0;
	virtual void setKockBack(float width,float acc) = 0;
	virtual sf::FloatRect getRect()const = 0;
	virtual sf::FloatRect getLastRect()const = 0;
	virtual void getFunc(Entity* entity) = 0;
	virtual void controlled(bool controlled) = 0;
	virtual void setDirection(direction d) = 0;
	virtual direction getDirection()const = 0;
	virtual void setRect(sf::FloatRect rect) = 0;
	virtual void setPosition(sf::FloatRect rect) = 0;
	virtual void setMove(bool move) = 0;
	virtual bool getMove()const = 0;
	virtual void setMaxSpeed(float speed) = 0;
	virtual float getMaxSpeed()const = 0;
	virtual void setLastSeenX(float lastSeen) = 0;
	virtual float getLastSeenX()const = 0;
	virtual sf::Texture* getTexture()const = 0;
	virtual void setTexture(sf::Texture* texture) = 0;
	virtual void tick(Entity *player, std::vector<Entity*> entityVector) = 0;
	virtual void render(sf::RenderTexture* window) = 0;
	virtual void toggleHiding() = 0;
	virtual layer getLayer() = 0;
	virtual bool getHiding() = 0;
	virtual bool getHunting() = 0;
	virtual bool getCanSeePlayer() = 0;
	virtual int getTypeID() = 0;
	virtual void setWait() = 0;
	virtual void resetTargetX() = 0;
};
#endif

