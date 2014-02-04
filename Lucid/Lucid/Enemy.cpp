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
	mWait = false;
	mWaitTime = 60;
	mViewBackRange = 50;
	mViewFrontRange = 300;
	mAggroRange = 100;
	mIsPlayerVisible = false;
	mTargetX = mPatrolStop;

	/*mFont.loadFromFile("../Debug/ariblk.ttf");
	mText.setFont(mFont);
	mText.setCharacterSize(24);
	mText.setColor(sf::Color::White);

	mWindow = new sf::RenderWindow(sf::VideoMode(300, 300, 32), "Enemy");*/
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
			if (mPlayerX > mRect.left - mViewBackRange && mPlayerX < mRect.left + mRect.width + mViewFrontRange && mDirection == RIGHT)
			{
				mTargetX = mPlayerX;
				if (mTargetX > mRect.left)
					mTargetX += mAggroRange;
				else
					mTargetX -= mAggroRange;
				mIsPlayerVisible = true;
			}
			else if (mPlayerX < mRect.left + mRect.width + mViewBackRange && mPlayerX > mRect.left - mViewFrontRange && mDirection == LEFT)
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
			if (mIsPlayerVisible == true)
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
			mIsPlayerVisible = false;
		}

		if (mRect.left <= mTargetX + 5 && mRect.left >= mTargetX - 5)
		{
			mWait = true;
			if (mTargetX == mPatrolStart)
				mTargetX = mPatrolStop;
			else
				mTargetX = mPatrolStart;
		}

		if (mWait == true)
		{
			mMove = false;

			mWaitTimer++;
			if (mWaitTimer >= mWaitTime)
			{
				mWait = false;
				mWaitTimer = 0;
			}
		}
		else
		{
			if(mTargetX < mRect.left)
			{
				mRect.left -= mMaxSpeed;
				mDirection = LEFT;
				mMove = true;
			}
			else if(mTargetX > mRect.left)
			{
				mRect.left += mMaxSpeed;
				mDirection = RIGHT;
				mMove = true;
			}
			else
				mMove = false;
		}

		if(mMove)
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

	/*std::string tempStr;
	tempStr = std::to_string(mRect.left);
	tempStr += " ";
	tempStr += std::to_string(mTargetX);
	tempStr += " ";
	tempStr += std::to_string(mWaitTimer);
	mText.setString(tempStr);*/

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
	
	/*mWindow->clear(sf::Color(255, 0, 255));
	mWindow->draw(mText);
	mWindow->display();*/
	window->draw(r);

	/*sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(mRect.width,0,-mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);*/
}