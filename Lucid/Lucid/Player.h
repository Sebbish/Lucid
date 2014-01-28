#pragma once
#include "entity.h"
class Player :
	public Entity
{
public:
	Player(sf::Vector2f position, sf::Vector2f Size,float speed);
	~Player();
	virtual sf::Vector2f getVector()const;
	virtual void setVector(sf::Vector2f); 
	virtual void setSpeed(int speed);
	virtual int getSpeed()const;
	virtual void setLastSeen(sf::Vector2f);
	virtual sf::Vector2f getLastSeen()const;
	virtual void tick();
	virtual void render();
private:
	sf::Vector2f mPosition;
	sf::Vector2f mLastSeen;
	sf::Vector2f mSize;
	float mSpeed;
};

