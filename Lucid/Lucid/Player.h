#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

class Player :
	public Entity
{
public:
	Player(float x, float y, float width, float height, float speed,sf::Texture* texture,float anitmationPicX,sf::SoundBuffer* walkSound, int typeID);
	~Player();
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
	virtual void setActive(bool active);
	virtual bool getActive();
	virtual void setTargetX(int x);
	virtual bool isEating();
	virtual void toggleRoofStance();
	virtual void hitRoof();
	virtual void shortYStepBack();
	virtual void tick(Entity *player, std::vector<Entity*> entityVector);
	virtual void render(sf::RenderTexture* window, bool visualizeValues, bool mirror, bool upsidedown);
	virtual void flashlight(bool flash);
	virtual void setImortal(bool imortal);
	virtual bool getImortal();
	virtual void setForm(form currentForm, form nextForm, bool upsidedown);
	virtual form getForm();
	virtual form getNextForm();
	virtual void setIdle();
private:
	float mLastSeenX;
	sf::FloatRect mRect;
	sf::FloatRect mLastRect;
	sf::FloatRect mSecondLastRect;
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
	bool mActive;
	int mAnimationY;
	bool mFlashlightMode;
	bool mImortal;
	float mAnimationSpeed;
	int mTypeID;
	sf::RectangleShape r;
	//int mBreatheDelay, mUpperBreatheDelay, mBreatheTimer, mUpperBreatheTimer;
};
#endif

