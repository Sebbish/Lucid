#include "Player.h"


Player::Player(sf::Vector2f position, sf::Vector2f Size,float speed):
	mPosition(position),mSize(Size),mMaxSpeed(speed)
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

void Player::setCurrentSpeed(float speed)
{
	mCurrentSpeed = speed;
}

float Player::getCurrentSpeed()const
{
	return mCurrentSpeed;
}

void Player::setMaxSpeed(float speed)
{
	mMaxSpeed = speed;
}

float Player::getMaxSpeed()const
{
	return mMaxSpeed;
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
	mPosition.x += mCurrentSpeed;
}

void Player::render(sf::RenderWindow* window)
{
	sf::RectangleShape r(mSize);
	r.setPosition(mPosition);
	window->draw(r);
}


