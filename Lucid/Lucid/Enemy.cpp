#include "Enemy.h"


Enemy::Enemy(sf::Vector2f position, sf::Vector2f size, float speed):
	mPosition(position), mSize(size), mSpeed(speed)
{
}


Enemy::~Enemy(void)
{
}

sf::Vector2f Enemy::getPosition()const
{
	return mPosition;
}

void Enemy::setPosition(sf::Vector2f position)
{
	mPosition = position;
}

sf::Vector2f Enemy::getSize()const
{
	return mSize;
}

void Enemy::setSize(sf::Vector2f size)
{
	mSize = size;
}

void  Enemy::setCurrentSpeed(float speed)
{
	mCurrentSpeed = speed;
}

float Enemy::getCurrentSpeed()const
{
	return mCurrentSpeed;
}

void Enemy::setMaxSpeed(float speed)
{
	mSpeed = speed;
}

float Enemy::getMaxSpeed()const
{
	return mSpeed;
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
	mPosition.x += mCurrentSpeed;
}

void Enemy::render(sf::RenderWindow* window)
{
	sf::RectangleShape r(mSize);
	r.setPosition(mPosition);
	window->draw(r);
}