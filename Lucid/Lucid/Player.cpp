#include "Player.h"


Player::Player(float x, float y, float width, float height,float speed,sf::Texture* texture,float anitmationPicX,sf::SoundBuffer* walkSound):
	mMaxSpeed(speed),mDirection(RIGHT),mTexture(texture),mAnimationPicX(anitmationPicX),mKnockWidth(0),mAcc(0)
{
	mRect.left = x;
	mRect.top = y;
	mRect.width = width;
	mRect.height = height;
	mAnimationTimer = 0.0f;
	mHiding = false;
	mLayer = Front;
	mWalkSound.setBuffer(*walkSound);
}


Player::~Player()
{
}

void Player::controlled(bool controlled)
{
	mControlled = controlled;
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

void Player::setKockBack(float width,float acc)
{
	mKnockWidth = width;
	mAcc = acc;
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

void Player::setLastSeenX(float lastSeenX)
{
	mLastSeenX = lastSeenX;
}

float Player::getLastSeenX()const
{
	return mLastSeenX;
}

sf::Texture* Player::getTexture()const
{
	return mTexture;
}

void Player::setTexture(sf::Texture* texture)
{
	mTexture = texture;
}

void Player::toggleHiding()
{
	mHiding = !mHiding;
	if (mLayer == Back)
		mLayer = Front;
	else
		mLayer = Back;
}

Player::layer Player::getLayer()
{
	return mLayer;
}

bool Player::getHiding()
{
	return mHiding;
}

bool Player::getHunting()
{
	return false;
}

bool Player::getCanSeePlayer()
{
	return false;
}

int Player::getTypeID()
{
	return 0;
}

void Player::setWait()
{
}

void Player::resetTargetX()
{

}

void Player::tick(Entity *player)
{
	mLastRect = mRect;
	if(mMove && mKnockWidth == 0 && !mHiding)
	{
		if(mDirection == Entity::RIGHT)
			mRect.left += mMaxSpeed;
		if(mDirection == Entity::LEFT)
			mRect.left -= mMaxSpeed;
		if(mAnimationTimer >= mAnimationPicX-0.1f)
			mAnimationTimer = 0.0f;
		else
			mAnimationTimer += 0.1f;

		if(mWalkSound.getStatus() != sf::Sound::Playing)
		{

			mWalkSound.play();
		}

	}
	else
	{
		mAnimationTimer = 0.0f;
		mWalkSound.stop();
	}

	if(mKnockWidth <= 1.9f && mKnockWidth >= -1.9f)
		mKnockWidth = 0;

	if(mKnockWidth != 0)
	{
		mKnockWidth = mKnockWidth*mAcc;
		mRect.left += mKnockWidth;
	}


}

void Player::render(sf::RenderTexture* window)
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
}
