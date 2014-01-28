#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
class Player :
	public Entity
{
public:
	Player(float x, float y, float width, float height,float speed);
	~Player();
	virtual sf::FloatRect getRect()const;
	virtual void setDirection(direction d);
	virtual direction getDirection()const;
	virtual void setRect(sf::FloatRect rect);
	virtual void setMove(bool move);
	virtual bool getMove()const;
	virtual void setMaxSpeed(float speed);
	virtual float getMaxSpeed()const;
	virtual void setLastSeen(sf::Vector2f lastSeen);
	virtual sf::Vector2f getLastSeen()const;
	virtual sf::Texture* getTexture()const;
	virtual void setTexture(sf::Texture* texture);
	virtual void tick();
	virtual void render(sf::RenderWindow* window);
private:
	sf::Vector2f mLastSeen;
	sf::FloatRect mRect;
	float mMaxSpeed;
	sf::Texture* mTexture;
	bool mMove;
	direction mDirection;
};
#endif

