#include "Player.h"

Player::Player(float x, float y, float width, float height,float speed,sf::Texture* texture,float anitmationPicX,sf::SoundBuffer* walkSound):
	mMaxSpeed(speed),mDirection(RIGHT),mTexture(texture),mAnimationPicX(anitmationPicX),mKnockWidth(0),mAcc(0)
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
	mMaxSpeed = dataVector[15];
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
	mActive = true;
	mFlashlightMode = false;
	mSecondLastRect = mRect;
	mMove = false;


	/*mBreatheDelay = 60 * 4;
	mUpperBreatheDelay = 60;
	mBreatheTimer = 0;
	mUpperBreatheTimer = 0;*/
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
	mAnimationTimer = 0;
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
	return 0;
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
	

	if(mMove && mKnockWidth == 0 && !mHiding)
	{
		if (mFlashlightMode == true  && mSecondLastRect != mRect)
		{
			mAnimationY = 1;
			mAnimationPicX = 11;
		}
		else if (mFlashlightMode == false  && mSecondLastRect != mRect)
		{
			mAnimationY = 0;
			mAnimationPicX = 8;
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
		if(mDirection == Entity::RIGHT)
			mRect.left += mMaxSpeed;
		if(mDirection == Entity::LEFT)
			mRect.left -= mMaxSpeed;
		if(mAnimationTimer >= mAnimationPicX-mAnimationSpeed)
			mAnimationTimer = 0.0f;
		else
			mAnimationTimer += mAnimationSpeed;

		if(mWalkSound.getStatus() != sf::Sound::Playing)
		{

			mWalkSound.play();
		}
	}
	else
	{
		if (mFlashlightMode == true)
		{
			mAnimationY = 3;
		}
		else
		{
			mAnimationY = 2;
		}
		mAnimationPicX = 4;
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

	if(mKnockWidth <= 1.9f && mKnockWidth >= -1.9f)
		mKnockWidth = 0;

	if(mKnockWidth != 0)
	{
		mKnockWidth = mKnockWidth*mAcc;
		mRect.left += mKnockWidth;
	}
	
	mSecondLastRect = mLastRect;

}

void Player::render(sf::RenderTexture* window, bool visualizeValues)
{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	if(mDirection == RIGHT)
		r.setTextureRect(sf::IntRect(mRect.width*(int)mAnimationTimer, mAnimationY * mRect.height,mRect.width,mRect.height));
	else if(mDirection == LEFT)
		r.setTextureRect(sf::IntRect(mRect.width*((int)mAnimationTimer+1),mAnimationY * mRect.height,-mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
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

