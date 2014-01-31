#include "Player.h"


Player::Player(float x, float y, float width, float height,float speed,sf::Texture* texture,float anitmationPicX):
	mMaxSpeed(speed),mDirection(RIGHT),mTexture(texture),mAnimationPicX(anitmationPicX)
{
	mRect.left = x;
	mRect.top = y;
	mRect.width = width;
	mRect.height = height;
	mAnimationTimer = 0.0f;
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

sf::FloatRect Player::getLastRect()const
{
	return mLastRect;
}

void Player::getFunc()
{

}

void Player::setRect(sf::FloatRect rect)
{
	mRect = rect;
}

void Player::setPosition(sf::FloatRect rect)
{
	mRect.left = rect.left;
	mRect.top = rect.top;
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

void Player::tick(Entity *player)
{
	if(mMove){
		mLastRect = mRect;
		if(mDirection == Entity::RIGHT)
			mRect.left += mMaxSpeed;
		if(mDirection == Entity::LEFT)
			mRect.left -= mMaxSpeed;
		if(mAnimationTimer >= mAnimationPicX-0.1f)
			mAnimationTimer = 0.0f;
		else
			mAnimationTimer += 0.1f;
	}else
		mAnimationTimer = 0.0f;
}

void Player::render(sf::RenderWindow* window)
{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(mRect.width*(int)mAnimationTimer,0,mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);
	
}
