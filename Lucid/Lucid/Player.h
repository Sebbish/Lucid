#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
class Player :
	public Entity
{
public:
	Player(float x, float y, float width, float height, float speed,sf::Texture* texture,float anitmationPicX,sf::SoundBuffer* walkSound);
	~Player();
	virtual sf::FloatRect getRect()const;
	virtual void setKockBack(float width,float acc);
	virtual sf::FloatRect getLastRect()const;
	virtual void getFunc(Entity* entity);
	virtual void controlled(bool controlled);
	virtual void setDirection(direction d);
	virtual direction getDirection()const;
	virtual void setRect(sf::FloatRect rect);
	virtual void setPosition(sf::FloatRect rect);
	virtual void setMove(bool move);
	virtual bool getMove()const;
	virtual void setMaxSpeed(float speed);
	virtual float getMaxSpeed()const;
	virtual void setLastSeenX(float lastSeenX);
	virtual float getLastSeenX()const;
	virtual sf::Texture* getTexture()const;
	virtual void setTexture(sf::Texture* texture);
	virtual void toggleHiding();
	virtual layer getLayer();
	virtual bool getHiding();
	virtual bool getHunting();
	virtual bool getCanSeePlayer();
	virtual int getTypeID();
	virtual void setWait();
	virtual void resetTargetX();
	virtual void tick(Entity *player, std::vector<Entity*> entityVector);
	virtual void render(sf::RenderTexture* window);
private:
	float mLastSeenX;
	sf::FloatRect mRect;
	sf::FloatRect mLastRect;
	float mMaxSpeed;
	sf::Texture* mTexture;
	bool mMove;
	direction mDirection;
	float mAnimationTimer;
	float mAnimationPicX;
	float mKnockWidth;
	float mAcc;
	bool mControlled;
	bool mHiding;
	layer mLayer;
	sf::Sound mWalkSound;

};
#endif

