#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
class Player :
	public Entity
{
public:
	Player(float x, float y, float width, float height, float speed,sf::Texture* texture,float anitmationPicX);
	~Player();
	virtual sf::FloatRect getRect()const;
	virtual void setKockBack(float width,float acc);
	virtual void getFunc();
	virtual void controlled(bool controlled);
	virtual void setDirection(direction d);
	virtual direction getDirection()const;
	virtual void setRect(sf::FloatRect rect);
	virtual void setMove(bool move);
	virtual bool getMove()const;
	virtual void setMaxSpeed(float speed);
	virtual float getMaxSpeed()const;
	virtual void setLastSeenX(float lastSeenX);
	virtual float getLastSeenX()const;
	virtual sf::Texture* getTexture()const;
	virtual void setTexture(sf::Texture* texture);
	virtual void tick(Entity *player);
	virtual void render(sf::RenderWindow* window);
private:
	float mLastSeenX;
	sf::FloatRect mRect;
	float mMaxSpeed;
	sf::Texture* mTexture;
	bool mMove;
	direction mDirection;
	float mAnimationTimer;
	float mAnimationPicX;
	float mKnockWidth;
	float mAcc;
	bool mControlled;
};
#endif

