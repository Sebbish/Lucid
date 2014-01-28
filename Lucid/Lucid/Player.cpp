#include "Player.h"


Player::Player(float x, float y, float width, float height,float speed):
	mMaxSpeed(speed),mDirection(RIGHT)
{
	mRect.left = x;
	mRect.top = y;
	mRect.width = width;
	mRect.height = height;
}


Player::~Player()
{
}

void Player::setDirection(direction d)
{
	mDirection = d;
}

Entity::direction Player::getDirection()const
{
	return mDirection;
}

sf::FloatRect Player::getRect()const
{
	return mRect;
}

void Player::setRect(sf::FloatRect rect)
{
	mRect = rect;
}

void Player::setMove(bool move)
{
	mMove = move;
}

bool Player::getMove()const
{
	return mMove;
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
	if(mMove){
		if(mDirection == Entity::RIGHT)
			mRect.left += mMaxSpeed;
		if(mDirection == Entity::LEFT)
			mRect.left -= mMaxSpeed;
	}
}

void Player::render(sf::RenderWindow* window)
{
	sf::RectangleShape r;
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
}
