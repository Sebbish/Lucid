#include "Enemy.h"


Enemy::Enemy(float x, float y, float width, float height,float speed, int direction, int patrolStart, int patrolStop, sf::Texture* texture, int typeID):
	mMaxSpeed(speed), mTexture(texture),mMove(false), mTypeID(typeID),mTempCollideWithPlayer(false),mControlled(false), mPatrolStart(patrolStart), mPatrolStop(patrolStop)
{
	mRect.left = x;
	mRect.top = y;
	mRect.width = width;
	mRect.height = height;
	mLastSeenX = x;
	if (direction == 0)
	{
		mDirection = LEFT;
	}
	else
	{
		mDirection = RIGHT;
	}
	mAnimationPicX = 2;
	mLayer = Front;
	mAnimationTimer = 0;
	mWaitTimer = 0;
	mWait = true;
	mWaitTime = 60;
	mViewBackRange = 50;
	mViewFrontRange = 300;
	mAggroRange = 100;
	mIsPlayerVisible = false;
}


Enemy::~Enemy(void)
{
}

void Enemy::controlled(bool controlled)
{
	mControlled = controlled;
}

void Enemy::setKockBack(float width,float acc)
{

}

void Enemy::setDirection(direction d)
{
	mDirection = d;
}

void Enemy::getFunc()
{
	mTempCollideWithPlayer = true;
}

Entity::direction Enemy::getDirection()const
{
	return mDirection;
}

sf::FloatRect Enemy::getRect()const
{
	return mRect;
}

sf::FloatRect Enemy::getLastRect()const
{
	return mLastRect;
}

void Enemy::setRect(sf::FloatRect rect)
{
	mRect = rect;
}

void Enemy::setPosition(sf::FloatRect rect)
{
}

void  Enemy::setMove(bool move)
{
	mMove = move;
}

bool Enemy::getMove()const
{
	return mMove;
}

void Enemy::setMaxSpeed(float speed)
{
	mMaxSpeed = speed;
}

float Enemy::getMaxSpeed()const
{
	return mMaxSpeed;
}

void Enemy::setLastSeenX(float lastSeenX)
{
	mLastSeenX = lastSeenX;
}

float Enemy::getLastSeenX()const
{
	return mLastSeenX;
}

sf::Texture* Enemy::getTexture()const
{
	return mTexture;
}

void Enemy::setTexture(sf::Texture* texture)
{
	mTexture = texture;
}

void Enemy::toggleHiding()
{
}

Enemy::layer Enemy::getLayer()
{
	return mLayer;
}

bool Enemy::getHiding()
{
	return false;
}

void Enemy::tick(Entity *player)
{
	if(!mControlled)
	{
		if (!player->getHiding())
		{
			mPlayerX = player->getRect().left;
			mHunting = false;
			if (mPlayerX > mRect.left - mViewBackRange && mPlayerX < mRect.left + mViewFrontRange && mDirection == RIGHT)
			{
				mTargetX = mPlayerX;
				if (mTargetX > mRect.left)
					mTargetX += mAggroRange;
				else
					mTargetX -= mAggroRange;
				mIsPlayerVisible = true;
			}
			else if (mPlayerX < mRect.left + mViewBackRange && mPlayerX > mRect.left - mViewFrontRange && mDirection == LEFT)
			{
				mTargetX = mPlayerX;
				if (mTargetX > mRect.left)
					mTargetX += mAggroRange;
				else
					mTargetX -= mAggroRange;
				mIsPlayerVisible = true;
			}
		}
		else
		{
			if (mIsPlayerVisible == false)
			{
				if (mDirection == RIGHT && player->getRect().left > mRect.left && player->getRect().left < mRect.left + mAggroRange)
				{
					mHunting = true;
				}
				else if (mDirection == LEFT && player->getRect().left < mRect.left && player->getRect().left > mRect.left - mAggroRange)
				{
					mHunting = true;
				}
			}
		}




		/*if (!player->getHiding())
		{
			if(player->getRect().top >= mRect.top-100 && player->getRect().top <= mRect.top+100)
			{

				if(player->getRect().left+player->getRect().width >= mRect.left-50 && player->getRect().left+player->getRect().width <= mRect.left)
				{
					mDirection = LEFT;

				}else if(player->getRect().left <= mRect.left+mRect.width+50 && player->getRect().left >= mRect.left+mRect.width)
				{
					mDirection = RIGHT;

				}

				if(player->getRect().left+player->getRect().width >= mRect.left-200 && player->getRect().left+player->getRect().width <= mRect.left && mDirection == LEFT)
				{
					mLastSeenX = player->getRect().left+player->getRect().width;

				}else if(player->getRect().left <= mRect.left+mRect.width+200 && player->getRect().left >= mRect.left+mRect.width && mDirection == RIGHT)
				{
					mLastSeenX = player->getRect().left;

				}
			}
		}

	
	if(mLastSeenX < mRect.left)
	{
		mRect.left -= mMaxSpeed;
		mMove = true;
	}else if(mLastSeenX > mRect.left+mRect.width)
	{
		mRect.left += mMaxSpeed;
		mMove = true;
	}else
		mMove = false;*/

	if (mWait = true)
	{
		mWaitTimer++;
		if (mWaitTimer >= mWaitTime)
			mWait = false;
	}

	if(mMove && mWait == false)
	{
		if(mAnimationTimer >= 1.9f)
		{
			mAnimationTimer = 0.0f;
		}
		else
			mAnimationTimer += 0.1f;
	}
	else
		mAnimationTimer = 0.0f;
	}
}

void Enemy::render(sf::RenderTexture* window)
{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	if(mDirection == RIGHT)
		r.setTextureRect(sf::IntRect(mRect.width*(int)mAnimationTimer,0,mRect.width,mRect.height));
	else if(mDirection == LEFT)
		r.setTextureRect(sf::IntRect(mRect.width*((int)mAnimationTimer+1),0,-mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);

	/*sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(mRect.width,0,-mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);*/
}