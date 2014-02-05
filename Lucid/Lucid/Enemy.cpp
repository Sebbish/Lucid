#include "Enemy.h"


Enemy::Enemy(float x, float y, float width, float height,float speed, int direction, int patrolStart, int patrolStop, sf::Texture* texture, int typeID,sf::SoundBuffer* walkSound,sf::SoundBuffer* jagaSound):
	mMaxSpeed(speed), mTexture(texture),mMove(false), mTypeID(typeID),mTempCollideWithPlayer(false),mControlled(false), mPatrolStart(patrolStart), mPatrolStop(patrolStop)
{
	mRect.left = x;
	mRect.top = y;
	mRect.width = width;
	mRect.height = height;
	mOriginalPosition = mRect;
	mLastSeenX = x;
	if (direction == 0)
	{
		mDirection = LEFT;
	}
	else
	{
		mDirection = RIGHT;
	}
	mAnimationPicX = 2;
	mLayer = Front;
	mAnimationTimer = 0;
	mWaitTimer = 0;
	mWait = false;
	mWaitTime = 60;
	mViewBackRange = 50;
	mViewFrontRange = 300;
	mAggroRange = 100;
	mIsPlayerVisible = false;
	mTargetX = mPatrolStop;
	mWalkSound.setBuffer(*walkSound);
	mJagaSound.setBuffer(*jagaSound);
	mTeleportWaitTime = 300;
	mTeleport = false;
	mTeleportTimer = 0;

	/*mFont.loadFromFile("../Debug/ariblk.ttf");
	mText.setFont(mFont);
	mText.setCharacterSize(24);
	mText.setColor(sf::Color::White);

	mWindow = new sf::RenderWindow(sf::VideoMode(300, 300, 32), "Enemy");*/
}


Enemy::~Enemy(void)
{
}

void Enemy::controlled(bool controlled)
{
	mControlled = controlled;
}

void Enemy::setKockBack(float width,float acc)
{

}

void Enemy::setDirection(direction d)
{
	mDirection = d;
}

void Enemy::getFunc()
{
	mTempCollideWithPlayer = true;
}

Entity::direction Enemy::getDirection()const
{
	return mDirection;
}

sf::FloatRect Enemy::getRect()const
{
	return mRect;
}

sf::FloatRect Enemy::getLastRect()const
{
	return mLastRect;
}

void Enemy::setRect(sf::FloatRect rect)
{
	mRect = rect;
}

void Enemy::setPosition(sf::FloatRect rect)
{
	mRect.left = rect.left;
	mRect.top = rect.top;
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

void Enemy::setLastSeenX(float lastSeenX)
{
	mLastSeenX = lastSeenX;
}

float Enemy::getLastSeenX()const
{
	return mLastSeenX;
}

sf::Texture* Enemy::getTexture()const
{
	return mTexture;
}

void Enemy::setTexture(sf::Texture* texture)
{
	mTexture = texture;
}

void Enemy::toggleHiding()
{
}

Enemy::layer Enemy::getLayer()
{
	return mLayer;
}

bool Enemy::getHiding()
{
	return false;
}

bool Enemy::getHunting()
{
	return mHunting;
}

bool Enemy::getCanSeePlayer()
{
	return mIsPlayerVisible;
}

int Enemy::getTypeID()
{
	return mTypeID;
}

void Enemy::setWait()
{
	mWait = true;
}

void Enemy::resetTargetX()
{
	if (mRect.top == mOriginalPosition.top) //Om den är på samma våning återgå till startpositionen
	{
		mTargetX = mPatrolStart;
	}
	else //Annars stå still
		mTargetX = mRect.left;
}

void Enemy::tick(Entity *player)
{
	if(!mControlled)
	{
		if (mRect.top != mOriginalPosition.top)
		{
			mTeleport = true;
		}
		mPlayerX = player->getRect().left;
		if (!player->getHiding())
		{
			mHunting = false;
			if (player->getRect().top > mRect.top - 50 && player->getRect().top < mRect.top + 50)
			{
				if (mPlayerX > mRect.left - mViewBackRange && mPlayerX < mRect.left + mViewFrontRange && mDirection == RIGHT)
				{
					mTargetX = mPlayerX;
					if (mTargetX > mRect.left)
					{
						mTargetX += mAggroRange;
					}
					else
					{
						mTargetX -= mAggroRange;
					}
					mIsPlayerVisible = true;
					mWait = false;
					mWaitTimer = 0;
					mTeleportTimer = 0; //Väntar med teleport om spelaren syns
				}
				else if (mPlayerX < mRect.left + mViewBackRange && mPlayerX > mRect.left - mViewFrontRange && mDirection == LEFT)
				{
					mTargetX = mPlayerX;
					if (mTargetX > mRect.left)
					{
						mTargetX += mAggroRange;
					}
					else
					{
						mTargetX -= mAggroRange;
					}
					mIsPlayerVisible = true;
					mWait = false;
					mWaitTimer = 0;
					mTeleportTimer = 0;
				}
			}
		}
		else
		{
			if (mIsPlayerVisible == true)
			{
				if (mDirection == RIGHT && mPlayerX > mRect.left && mPlayerX < mRect.left + mAggroRange)
				{
					mHunting = true;
				}
				else if (mDirection == LEFT && mPlayerX < mRect.left && mPlayerX > mRect.left - mAggroRange)
				{
					mHunting = true;
				}
			}
			mIsPlayerVisible = false;
		}

		if (mRect.left <= mTargetX + 5 && mRect.left >= mTargetX - 5)
		{
			mWait = true;
			if (!mTeleport)//Patrullerar inte om den ska teleportera, då jagar den spelaren eller står still
			{
				if (mTargetX == mPatrolStart)
					mTargetX = mPatrolStop;
				else
					mTargetX = mPatrolStart;
			}
		}

		if (mWait)
		{
			mMove = false;
			mWaitTimer++;
			if (mWaitTimer >= mWaitTime)
			{
				mWait = false;
				mWaitTimer = 0;
			}
			
		}
		else
		{
			if(mTargetX < mRect.left)
			{
				mRect.left -= mMaxSpeed;
				mDirection = LEFT;
				mMove = true;
			}
			else if(mTargetX > mRect.left)
			{
				mRect.left += mMaxSpeed;
				mDirection = RIGHT;
				mMove = true;
			}
			else
				mMove = false;
		}

		if (mTeleport)
		{
			mTeleportTimer++;
			if (mTeleportTimer >= mTeleportWaitTime)
			{
				mRect = mOriginalPosition;
				mTeleportTimer = 0;
				mTeleport = false;
				mWait = true;
				mTargetX = mPatrolStop;
			}
		}
	}

	else
	{
		if (mMove)
		{
			if (mDirection == LEFT)
			{
				mRect.left -= mMaxSpeed;
			}
			else
			{
				mRect.left += mMaxSpeed;
			}
		}
	}

	if(mMove)
		{
			if(mAnimationTimer >= 1.9f)
			{
				mAnimationTimer = 0.0f;
			}
			else
				mAnimationTimer += 0.1f;
		}
		else
			mAnimationTimer = 0.0f;
	/*std::string tempStr;
	tempStr = std::to_string(mRect.left);
	tempStr += " ";
	tempStr += std::to_string(mTargetX);
	tempStr += " ";
	tempStr += std::to_string(mWaitTimer);
	mText.setString(tempStr);*/

	if(mMove)
	{
		if(mWalkSound.getStatus() != sf::Sound::Playing)
		{

			mWalkSound.play();
		}
	}else
		mWalkSound.stop();

	if(mIsPlayerVisible)
	{
		if(mJagaSound.getStatus() != sf::Sound::Playing)
		{
			mJagaSound.play();
		}
	}else
		mJagaSound.stop();

}

void Enemy::render(sf::RenderTexture* window)
{
	sf::RectangleShape r;
	r.setTexture(mTexture);
	if(mDirection == RIGHT)
		r.setTextureRect(sf::IntRect(mRect.width*(int)mAnimationTimer,0,mRect.width,mRect.height));
	else if(mDirection == LEFT)
		r.setTextureRect(sf::IntRect(mRect.width*((int)mAnimationTimer+1),0,-mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	
	/*mWindow->clear(sf::Color(255, 0, 255));
	mWindow->draw(mText);
	mWindow->display();*/
	window->draw(r);

	/*sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(mRect.width,0,-mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);*/
}