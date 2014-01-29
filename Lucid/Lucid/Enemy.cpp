#include "Enemy.h"


Enemy::Enemy(float x, float y, float width, float height,float speed):
	mMaxSpeed(speed)
{
	mRect.left = x;
	mRect.top = y;
	mRect.width = width;
	mRect.height = height;
}


Enemy::~Enemy(void)
{
}

void Enemy::setDirection(direction d)
{
	mDirection = d;
}

void Enemy::getFunc()
{
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

void Enemy::tick(Entity *player)
{
	if(player->getRect().left+player->getRect().width <= mRect.left)
	{
		mDirection = LEFT;
		mRect.left -= mMaxSpeed;
	}else if(mRect.left+mRect.width <= player->getRect().left)
	{
		mDirection = RIGHT;
		mRect.left += mMaxSpeed;
	}
}

void Enemy::render(sf::RenderWindow* window)
{
	sf::RectangleShape r;
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
}