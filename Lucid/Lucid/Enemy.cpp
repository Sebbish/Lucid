#include "Enemy.h"


Enemy::Enemy(float x, float y, float width, float height,float speed, int direction, sf::Texture* texture, int typeID):
	mMaxSpeed(speed), mTexture(texture),mMove(false), mTypeID(typeID),mTempCollideWithPlayer(false)
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

void Enemy::tick(Entity *player)
{
	if(!mControlled)
	{
	if(player->getRect().left+player->getRect().width >= mRect.left-200)
	{
		mDirection = LEFT;
		mLastSeenX = player->getRect().left;

	}else if(player->getRect().left >= mRect.left+mRect.width+200)
	{
		mDirection = RIGHT;
		mLastSeenX = player->getRect().left;

	}
	if(mTempCollideWithPlayer)
	{
		mMove = false;
		if(mDirection == LEFT)
		{
			player->setKockBack(-30.0f,0.9f);
			mTempCollideWithPlayer = false;
		}else
		{
			player->setKockBack(30.0f,0.9f);
			mTempCollideWithPlayer = false;
		}
	}else{
		if(mLastSeenX < mRect.left)
		{
			mRect.left -= mMaxSpeed;
			mMove = true;
		}else if(mLastSeenX > mRect.left+mRect.width)
		{
			mRect.left += mMaxSpeed;
			mMove = true;
		}else
			mMove = false;

		if(mMove)
		{
		if(mAnimationTimer >= 1.9f)
			mAnimationTimer = 0.0f;
		else
			mAnimationTimer += 0.1f;
		}else
			mAnimationTimer = 0.0f;
	}
	}
}

void Enemy::render(sf::RenderWindow* window)
{
	if(mDirection == RIGHT)
	{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(mRect.width*(int)mAnimationTimer,0,mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
	}else if(mDirection == LEFT)
	{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(mRect.width*((int)mAnimationTimer+1),0,-mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
	}
}