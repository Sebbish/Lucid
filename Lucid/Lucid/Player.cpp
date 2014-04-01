#include "Player.h"

Player::Player(float x, float y, float width, float height,float speed,sf::Texture* texture,float anitmationPicX,sf::SoundBuffer* walkSound, int typeID):
	mMaxSpeed(speed),mDirection(RIGHT),mTexture(texture),mAnimationPicX(anitmationPicX),mKnockWidth(0),mAcc(0), mTypeID(typeID)
{
	std::ifstream stream;
	stream.open("../Debug/config.txt");
	std::string output;
	std::vector<int> dataVector;
	while(!stream.eof())
	{
		stream >> output;
		dataVector.push_back(atoi(output.c_str()));
	}
	stream.close();
	stream.clear();
	mMaxSpeed = dataVector[15] / 10;
	int mAnimationY = 0;

	mRect.left = x;
	mRect.top = y;
	mRect.width = width;
	mRect.height = height;
	mAnimationTimer = 0.0f;
	mAnimationSpeed = 0.15f;
	mHiding = false;
	mImortal = false;
	mLayer = Front;
	mWalkSound.setBuffer(*walkSound);
	//mWalkSound.setPitch(2.2f);
	//mWalkSound.setPitch(1.6f);
	mActive = true;
	mFlashlightMode = false;
	mSecondLastRect = mRect;
	mMove = false;
	
	/*mBreatheDelay = 60 * 4;
	mUpperBreatheDelay = 60;
	mBreatheTimer = 0;
	mUpperBreatheTimer = 0;*/
	r.setTexture(mTexture);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
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

sf::FloatRect Player::getHitBox()const
{
	sf::FloatRect hitBoxRect = mRect;
	hitBoxRect.left += 100;
	hitBoxRect.top += 50;
	hitBoxRect.height = 206;
	hitBoxRect.width = 56;
	return hitBoxRect;
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

void Player::getFunc(Entity* entity)
{

}

void Player::setRect(sf::FloatRect rect)
{
	mRect = rect;
	//mAnimationTimer = 0;
	mMove = false;
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
	if (mSecondLastRect == mRect)
		return false;
	else
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

bool Player::getSearching()
{
	return false;
}

bool Player::getCanSeePlayer()
{
	return false;
}

int Player::getTypeID()
{
	return mTypeID;
}

void Player::setWait()
{
}

void Player::resetTargetX()
{

}

void Player::setActive(bool active)
{
	mActive = active;
}

bool Player::getActive()
{
	return mActive;
}

void Player::setTargetX(int x)
{
}

bool Player::isEating()
{
	return false;
}

void Player::toggleRoofStance()
{
}

void Player::hitRoof()
{
}

void Player::shortYStepBack()
{
}

void Player::tick(Entity *player, std::vector<Entity*> entityVector)
{
	mLastRect = mRect;
	
	if(mWalkSound.getPlayingOffset().asSeconds() >= 1)
		mWalkSound.stop();

	if(mMove && mKnockWidth == 0 && !mHiding)
	{
		if (mFlashlightMode == true  && mSecondLastRect != mRect)
		{
			mAnimationY = 1;
			mAnimationPicX = 12;
			mWalkSound.setPitch(1.6f);
		}
		else if (mFlashlightMode == false  && mSecondLastRect != mRect)
		{
			mAnimationY = 0;
			mAnimationPicX = 8;
			mWalkSound.setPitch(2.2f);
		}
		else if ((mFlashlightMode == true  && mSecondLastRect == mRect))
		{
			mAnimationY = 3;
			mAnimationPicX = 4;
		}
		else
		{
			mAnimationY = 2;
			mAnimationPicX = 4;
		}

		if (mTypeID == 69 || mTypeID == 29)
		{
			mAnimationPicX = 8;
			mAnimationY = 0;
		}

		if(mDirection == Entity::RIGHT)
			mRect.left += mMaxSpeed;
		if(mDirection == Entity::LEFT)
			mRect.left -= mMaxSpeed;
		if(mAnimationTimer >= mAnimationPicX-mAnimationSpeed)
		{
			mAnimationTimer = 0.0f;
			mWalkSound.play();
		}else
			mAnimationTimer += mAnimationSpeed;

		/*if(mWalkSound.getStatus() != sf::Sound::Playing)
		{

			mWalkSound.play();
		}*/
		if(mWalkSound.getStatus() == sf::Sound::Stopped)
			mWalkSound.play();
	}
	else if(!mMove && mKnockWidth == 0 && !mHiding)
	{
		if (mTypeID == 0)
		{
			if (mFlashlightMode == true)
			{
				mAnimationY = 3;
			}
			else
			{
				mAnimationY = 2;
			}
		}
		else
		{
			mAnimationY = 1;
		}
		mAnimationPicX = 8;
		if(mAnimationTimer >= mAnimationPicX-mAnimationSpeed)
		{
			mAnimationTimer = 0.0f;
			//mBreatheTimer = 0;
		}
		/*if(mAnimationTimer == mAnimationPicX / 2)
		{
			mUpperBreatheTimer = 0;
		}*/
		else //if (mBreatheTimer >= mBreatheDelay && mUpperBreatheTimer >= mUpperBreatheDelay)
		{
			mAnimationTimer += mAnimationSpeed;
		}
		//mBreatheTimer++;
		//mUpperBreatheTimer++;
		mWalkSound.stop();
	}
	else if (mHiding)
	{
		mAnimationY = 4;
		mAnimationPicX = 0;

		if(mAnimationTimer >= mAnimationPicX-mAnimationSpeed)
		{
			mAnimationTimer = 0.0f;
			mWalkSound.play();
		}else
			mAnimationTimer += mAnimationSpeed;
	}

	if(mKnockWidth <= 1.9f && mKnockWidth >= -1.9f)
		mKnockWidth = 0;

	if(mKnockWidth != 0)
	{
		mKnockWidth = mKnockWidth*mAcc;
		mRect.left += mKnockWidth;
	}
	
	
	mSecondLastRect = mLastRect;

}

void Player::render(sf::RenderTexture* window, bool visualizeValues, bool mirror, bool upsidedown)
{
	if (!mMove && !mHiding)
	{
	if (mTypeID == 0)
		{
			if (mFlashlightMode == true)
			{
				mAnimationY = 3;
			}
			else
			{
				mAnimationY = 2;
			}
		}
		else
		{
			mAnimationY = 1;
		}
	}

	
	if (!mirror)
	{
		if(mDirection == RIGHT)
		{
			if (!upsidedown)
				r.setTextureRect(sf::IntRect(mRect.width*(int)mAnimationTimer, mAnimationY * mRect.height,mRect.width,mRect.height));
			else
				r.setTextureRect(sf::IntRect(mRect.width*(int)mAnimationTimer, (mAnimationY + 1) * mRect.height,mRect.width,-mRect.height));
			if (mHiding)
			{
				r.setPosition(mRect.left + 35,mRect.top);
			}
			else
			{
				r.setPosition(mRect.left,mRect.top);
			}
		}
		else if(mDirection == LEFT)
		{
			if (!upsidedown)
				r.setTextureRect(sf::IntRect(mRect.width*((int)mAnimationTimer+1),mAnimationY * mRect.height,-mRect.width,mRect.height));
			else
				r.setTextureRect(sf::IntRect(mRect.width*((int)mAnimationTimer+1),(mAnimationY + 1) * mRect.height,-mRect.width,-mRect.height));
			if (mHiding)
			{
				r.setPosition(mRect.left - 50,mRect.top);
			}
			else
			{
				r.setPosition(mRect.left,mRect.top);
			}
		}

	}
	else
	{
		float tempTimer = mAnimationTimer;
		if (mMove)
			tempTimer += 4;
		if (tempTimer > mAnimationPicX)
			tempTimer -= 8;
		if(mDirection == RIGHT)
		{
			r.setTextureRect(sf::IntRect(mRect.width*(int)tempTimer, mAnimationY * mRect.height,mRect.width,mRect.height));
			r.setPosition(mRect.left + 10,mRect.top);
		}
		else if(mDirection == LEFT)
		{
			r.setTextureRect(sf::IntRect(mRect.width*((int)tempTimer+1),mAnimationY * mRect.height,-mRect.width,mRect.height));
			r.setPosition(mRect.left - 10,mRect.top);
		}
		
	}
	window->draw(r);

	if (visualizeValues)
	{
		sf::CircleShape circle(6);
		circle.setPosition(mRect.left - 3, mRect.top - 3);
		window->draw(circle);
	}
}

void Player::flashlight(bool flash)
{
	mFlashlightMode = flash;
}

void Player::setImortal(bool imortal)
{
	mImortal = imortal;
}

bool Player::getImortal()
{
	return mImortal;
}

void Player::setForm(form currentForm, form nextForm, bool upsidedown)
{
}

Entity::form Player::getForm()
{
	return NONE;
}

Entity::form Player::getNextForm()
{
	return NONE;
}

void Player::setIdle()
{

}