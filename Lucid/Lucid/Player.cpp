#include "Player.h"


Player::Player(sf::Vector2f position, sf::Vector2f Size,float speed):
	mPosition(position),mSize(Size),mSpeed(speed)
{
}


Player::~Player()
{
}

sf::Vector2f Player::getPosition()const
{
	return mPosition;
}

void Player::setPosition(sf::Vector2f position)
{
	mPosition = position;
}

sf::Vector2f Player::getSize()const
{
	return mSize;
}

void Player::setSize(sf::Vector2f size)
{
	mSize = size;
}

void Player::setSpeed(float speed)
{
	mSpeed = speed;
}

float Player::getSpeed()const
{
	return mSpeed;
}

void Player::setLastSeen(sf::Vector2f lastSeen)
{
	mLastSeen = lastSeen;
}

sf::Vector2f Player::getLastSeen()const
{
	return mLastSeen;
}

sf::Texture* Player::getTexture()const
{
	return mTexture;
}

void Player::setTexture(sf::Texture* texture)
{
	mTexture = texture;
}

void Player::tick()
{

}

void Player::render()
{

}


