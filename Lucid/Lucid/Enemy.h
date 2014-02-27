#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"

class Enemy :
	public Entity
{
public:
	Enemy(float x, float y, float width, float height, float speed, int direction, int patrolStart, int patrolStop, sf::Texture* texture, int typeID, int active, sf::SoundBuffer* walkSound,sf::SoundBuffer* jagaSound);
	~Enemy();
	virtual sf::FloatRect getRect()const;
	virtual sf::FloatRect getHitBox()const;
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
	virtual bool getSearching();
	virtual bool getCanSeePlayer();
	virtual int getTypeID();
	virtual void setWait();
	virtual void resetTargetX();
	virtual void tick(Entity *player, std::vector<Entity*> entityVector);
	virtual void render(sf::RenderTexture* window, bool visualizeValues);
	virtual void setActive(bool active);
	virtual bool getActive();
	virtual void setTargetX(int x);
	virtual bool isEating();
	virtual void toggleRoofStance();
	virtual void hitRoof();
	virtual void shortYStepBack();
	virtual void flashlight(bool flash);
	
private:
	float mLastSeenX;
	sf::FloatRect mRect;
	sf::FloatRect mLastRect;
	float mMaxSpeed;
	float mHuntingSpeed;
	sf::Texture* mTexture;
	bool mMove;
	direction mDirection;
	int mTypeID;
	bool mTempCollideWithPlayer;
	float mAnimationTimer;
	float mAnimationPicX;
	float mAnimationSpeed;
	bool mControlled;
	int mPatrolStart;
	int mPatrolStop;
	layer mLayer;
	bool mWait;
	bool mHunting;
	bool mIsPlayerVisible;
	bool mSearching;
	bool mWalkTransition;
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
	bool mActive;
	void checkSight(Entity* entity);
	void setAnimation();

	sf::FloatRect mOriginalPosition;
	bool mTeleport;
	int mTeleportWaitTime;
	int mTeleportTimer;
	enum form
	{
		SLIME,
		MONSTER,
		EAT,
		ROOFCHANGING,
		ROOFTRAVEL,
		ROOFCHANGINGBACK,
		ROOF
	};
	form mCurrentForm;
	form mNextForm;
	int mAnimationY;
	//sf::RenderWindow* mWindow;
	bool upsidedown;
};
#endif