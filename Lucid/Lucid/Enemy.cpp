#include "Enemy.h"


Enemy::Enemy(float x, float y, float width, float height,float speed, int direction, sf::Texture* texture):
	mMaxSpeed(speed), mTexture(texture)
{
	mRect.left = x;
	mRect.top = y;
	mRect.width = width;
	mRect.height = height;
	if (direction == 0)
	{
		mDirection = LEFT;
	}
	else
	{
		mDirection = RIGHT;
	}
}


Enemy::~Enemy(void)
{
}

void Enemy::setDirection(direction d)
{
	mDirection = d;
}

Entity::direction Enemy::getDirection()const
{
	return mDirection;
}

sf::FloatRect Enemy::getRect()const
{
	return mRect;
}

void Enemy::setRect(sf::FloatRect rect)
{
	mRect = rect;
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

void Enemy::setLastSeen(sf::Vector2f lastSeen)
{
	mLastSeen = lastSeen;
}

sf::Vector2f Enemy::getLastSeen()const
{
	return mLastSeen;
}

sf::Texture* Enemy::getTexture()const
{
	return mTexture;
}

void Enemy::setTexture(sf::Texture* texture)
{
	mTexture = texture;
}

void Enemy::tick()
{
	if(mMove){
		if(mDirection == Entity::RIGHT)
			mRect.left += mMaxSpeed;
		if(mDirection == Entity::LEFT)
			mRect.left -= mMaxSpeed;
	}
}

void Enemy::render(sf::RenderWindow* window)
{
	sf::RectangleShape r;
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
}