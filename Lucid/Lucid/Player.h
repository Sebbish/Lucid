#pragma once
#include "entity.h"
class Player :
	public Entity
{
public:
	Player(sf::Vector2f position, sf::Vector2f Size,float speed);
	~Player();
	virtual sf::Vector2f getPosition()const;
	virtual void setPosition(sf::Vector2f position);
	virtual sf::Vector2f getSize()const ;
	virtual void setSize(sf::Vector2f size);
	virtual void setSpeed(float speed);
	virtual float getSpeed()const;
	virtual void setLastSeen(sf::Vector2f lastSeen);
	virtual sf::Vector2f getLastSeen()const;
	virtual sf::Texture* getTexture()const;
	virtual void setTexture(sf::Texture* texture);
	virtual void tick();
	virtual void render();
private:
	sf::Vector2f mPosition;
	sf::Vector2f mLastSeen;
	sf::Vector2f mSize;
	float mSpeed;
	sf::Texture* mTexture;
};

