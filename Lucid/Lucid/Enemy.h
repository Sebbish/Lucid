#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
class Enemy :
	public Entity
{
public:
	Enemy(float x, float y, float width, float height, float speed, int direction, int patrolStart, int patrolStop, sf::Texture* texture, int typeID,sf::SoundBuffer* walkSound,sf::SoundBuffer* jagaSound);
	~Enemy();
	virtual sf::FloatRect getRect()const;
	virtual void setKockBack(float width,float acc);
	virtual sf::FloatRect getLastRect()const;
	virtual void getFunc();
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
	virtual void tick(Entity *player);
	virtual void render(sf::RenderTexture* window);
	
private:
	float mLastSeenX;
	sf::FloatRect mRect;
	sf::FloatRect mLastRect;
	float mMaxSpeed;
	sf::Texture* mTexture;
	bool mMove;
	direction mDirection;
	int mTypeID;
	bool mTempCollideWithPlayer;
	float mAnimationTimer;
	float mAnimationPicX;
	bool mControlled;
	int mPatrolStart;
	int mPatrolStop;
	layer mLayer;
	bool mWait;
	bool mHunting;
	bool mIsPlayerVisible;
	int mWaitTimer;
	int mWaitTime;
	int mTargetX;
	int mViewBackRange, mViewFrontRange;
	int mAggroRange;
	int mPlayerX;
	sf::Font mFont;
	sf::Text mText;
	sf::Sound mWalkSound;
	sf::Sound mJagaSound;

	sf::FloatRect mOriginalPosition;
	bool mTeleport;
	int mTeleportWaitTime;
	int mTeleportTimer;


	//sf::RenderWindow* mWindow;
};
#endif