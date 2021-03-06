#include "Enemy.h"

Enemy::Enemy(float x, float y, float width, float height, float speed, int direction, int patrolStart, int patrolStop, sf::Texture* texture, int typeID, int active, sf::SoundBuffer* walkSound,sf::SoundBuffer* attack,sf::SoundBuffer* morphSound,sf::SoundBuffer* walkNotSlimeSound):
	mMaxSpeed(speed), mTexture(texture),mMove(false), mTypeID(typeID),mTempCollideWithPlayer(false),mControlled(false), mPatrolStart(patrolStart), mPatrolStop(patrolStop)
{
	std::ifstream stream;
	stream.open("config.txt");
	std::string output;
	std::vector<int> dataVector;
	while(!stream.eof())
	{
		stream >> output;
		dataVector.push_back(atoi(output.c_str()));
	}
	stream.close();
	stream.clear();
	if (mTypeID == 21)
	{
		mMaxSpeed = (float)dataVector[2] / 10;
		mHuntingSpeed = (float)dataVector[4] / 10;
		mChasingSpeed = (float)dataVector[30] / 10;
		mControlledSpeed = (float)dataVector[32] / 10;
		mAnimationPicX = 4;
		mAnimationSpeed = 0.15;
	}
	else
	{
		mMaxSpeed = 3;
		mHuntingSpeed = 4;
		mChasingSpeed = 4;
		mControlledSpeed = 0;
		mAnimationPicX = 8;
		mAnimationSpeed = 0.2;
	}
	/*mChasingSpeed = 6.7;
	mControlledSpeed = 6;*/

	mFlightSpeed = 24;

	mWaitTime = dataVector[6];
	mViewFrontRange = dataVector[8];
	mViewBackRange = dataVector[10];
	mAggroRange = dataVector[12];



	mRect.left = x;
	mRect.top = y;
	mRect.width = width;
	mRect.height = height;
	mOriginalPosition = mRect;
	mLastSeenX = x;
	if (direction == 0)
	{
		mDirection = LEFT;
		mOriginalDirection = LEFT;
	}
	else
	{
		mDirection = RIGHT;
		mOriginalDirection = RIGHT;
	}
	mLayer = Front;
	mAnimationTimer = 0;
	mWaitTimer = 0;
	mWait = false;
	mEatWait = false;
	mEatWaitTime = 240;
	mEatWaitTimer = 0;
	mImortal = false;
	//mWaitTime = 60;
	/*mViewBackRange = 300;
	mViewFrontRange = 800;
	mAggroRange = 400;*/
	mIsPlayerVisible = false;
	mTargetX = mPatrolStop;

	mWalkSound.setBuffer(*walkSound);
	mMorphSound.setBuffer(*morphSound);
	mWalkNotSlimeSound.setBuffer(*walkNotSlimeSound);
	mAttackSound.setBuffer(*attack);

	mWalkSound.setMinDistance(1000);
	mWalkSound.setAttenuation(10);
	mMorphSound.setMinDistance(1000);
	mMorphSound.setAttenuation(10);
	mWalkNotSlimeSound.setMinDistance(1000);
	mWalkNotSlimeSound.setAttenuation(10);
	mAttackSound.setMinDistance(1000);
	mAttackSound.setAttenuation(10);

	mIdle = false;


	mTeleportWaitTime = 300;
	mTeleport = false;
	mTeleportTimer = 0;
	if (active == 0)
		mActive = false;
	else
		mActive = true;
	mCurrentForm = SLIME;
	mNextForm = SLIME;

	mSearching = false;

	mUpsidedown = false;

	r.setTexture(mTexture);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));

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

void Enemy::getFunc(Entity* entity)
{
	if (mActive && !mIdle)
	{
		if (entity->getTypeID() == 0)
		{
			mNextForm = EAT;
			if(mAttackSound.getStatus() != sf::Sound::Playing)
				mAttackSound.play();
		}
		if (entity->getTypeID() == 22 && mTypeID == 21)
		{
			mRect.left = -5000;
			mRect.top = -5000;
		}
		if (entity->getTypeID() == 21 && mTypeID == 22)
		{
			mNextForm = EAT;
			if(mAttackSound.getStatus() != sf::Sound::Playing)
				mAttackSound.play();
		}
		/*if (entity->getTypeID() == 0 && (mTypeID == 2 || mTypeID == 6) && (!entity->getHiding() || mHunting))
		{

		}*/
	}
}

Entity::direction Enemy::getDirection()const
{
	return mDirection;
}

sf::FloatRect Enemy::getRect()const
{
	return mRect;
}

sf::FloatRect Enemy::getHitBox()const
{
	if (!mIdle)
	{
	sf::FloatRect hitBoxRect = mRect;
	/*hitBoxRect.left += 80;
	hitBoxRect.width = 96;*/
	hitBoxRect.left += 53;
	hitBoxRect.width = 150;
	if (mCurrentForm == ROOFTRAVEL)
	{
		if (!mUpsidedown)
		{
			hitBoxRect.height = 128;
		}
		else
		{
			hitBoxRect.top += 128;
			hitBoxRect.height = 128;
		}
	}
	else if (!mUpsidedown)
	{
		//hitBoxRect.top += 100;
		//hitBoxRect.height = 156;
		hitBoxRect.top += 196;
		hitBoxRect.height = 60;
	}
	else
	{
		//hitBoxRect.top += 100;
		//hitBoxRect.height = 156;
		hitBoxRect.height = 60;
	}
	return hitBoxRect;
	}
	else
		return sf::FloatRect(0, 0, 0, 0);
}

sf::FloatRect Enemy::getLastRect()const
{
	return mLastRect;
}

void Enemy::setRect(sf::FloatRect rect)
{
	mRect = rect;
	if (mCurrentForm != ROOFTRAVEL)
		mAnimationTimer = 0;
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

bool Enemy::getSearching()
{
	return mSearching;
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
	if (mRect.top == mOriginalPosition.top) //Om den �r p� samma v�ning �terg� till startpositionen
	{
		mTargetX = mPatrolStart;
	}
	else //Annars st� still
		mTargetX = mRect.left;
}

void Enemy::checkSight(Entity *entity)
{
	mPlayerX = entity->getRect().left;
	if (!entity->getHiding())
	{
		mHunting = false;
		if (entity->getRect().top > mRect.top - 50 && entity->getRect().top < mRect.top + 50)
		{
			if (mPlayerX > mRect.left - mViewBackRange && mPlayerX < mRect.left + mViewFrontRange && mDirection == RIGHT)
			{
				mTargetX = mPlayerX;
				if (mTargetX > mRect.left)
				{
					if (entity->getTypeID() == 22 && mTypeID == 21)
						mTargetX -= mViewFrontRange + mAggroRange * 2;
					else if (mTypeID == 21)
						mTargetX += mAggroRange * 2;
				}
				else
				{
					if (entity->getTypeID() == 22 && mTypeID == 21)
						mTargetX += mViewFrontRange + mAggroRange * 2;
					else if (mTypeID == 21)
						mTargetX -= mAggroRange * 2;
				}
				mIsPlayerVisible = true;
				mSearching = true;
				mWait = false;
				mWaitTimer = 0;
				mTeleportTimer = 0; //V�ntar med teleport om spelaren syns

				if (mPlayerX > mRect.left && mPlayerX < mRect.left + mAggroRange)
					{
						mHunting = true;
					}
			}
			else if (mPlayerX < mRect.left + mViewBackRange && mPlayerX > mRect.left - mViewFrontRange && mDirection == LEFT)
			{
				mTargetX = mPlayerX;
				if (mTargetX > mRect.left)
				{
					if (entity->getTypeID() == 22 && mTypeID == 21)
						mTargetX -= mViewFrontRange + mAggroRange * 2;
					else if (mTypeID == 21)
						mTargetX += mAggroRange * 2;
				}
				else
				{
					if (entity->getTypeID() == 22 && mTypeID == 21)
						mTargetX += mViewFrontRange + mAggroRange * 2;
					else if (mTypeID == 21)
					mTargetX -= mAggroRange * 2;
				}
				mIsPlayerVisible = true;
				mSearching = true;
				mWait = false;
				mWaitTimer = 0;
				mTeleportTimer = 0;

				if (mPlayerX < mRect.left && mPlayerX > mRect.left - mAggroRange)
					{
						mHunting = true;
					}
			}
			else
			{
				mIsPlayerVisible = false;
			}
		}
		else
			mIsPlayerVisible = false;
	}
	else
	{
		mIsPlayerVisible = false;
	}
}

void Enemy::setActive(bool active)
{
	mActive = active;
}

bool Enemy::getActive()
{
	return mActive;
}

void Enemy::setTargetX(int x)
{
	mTargetX = x;
}

bool Enemy::isEating()
{
	if (mCurrentForm == EAT || mNextForm == EAT)
		return true;
	else
		return false;
}

void Enemy::setForm(form currentForm, form nextForm, bool upsidedown)
{
	if (currentForm != NONE)
		mCurrentForm = currentForm;
	if (nextForm != NONE)
		mNextForm = nextForm;
	mUpsidedown = upsidedown;
	if (mNextForm == EAT && mCurrentForm == SLIME)
	{
		mAnimationPicX = 4;
		mAnimationY = 6;
		mAnimationTimer = 0;
	}
}

Entity::form Enemy::getForm()
{
	return mCurrentForm;
}

Entity::form Enemy::getNextForm()
{
	return mNextForm;
}

void Enemy::toggleRoofStance()
{
	if (mCurrentForm != ROOF && mNextForm != ROOF)
	{
		mNextForm = ROOF;
		mCurrentForm = ROOFCHANGING;
		mAnimationTimer = 0;
		mAnimationPicX = 4;
		mAnimationY = 0;
	}
	else if (mCurrentForm == ROOF)
	{
		mNextForm = ROOF;
		mCurrentForm = ROOFCHANGING;
		mAnimationTimer = 0;
		mAnimationPicX = 4;
		mAnimationY = 0;
	}
}

void Enemy::hitRoof()
{
	if (mCurrentForm == ROOFTRAVEL)
	{
		mUpsidedown = !mUpsidedown;
		mCurrentForm = ROOFCHANGINGBACK;
		mAnimationTimer = mAnimationPicX - mAnimationSpeed;
		mAnimationY = 0;
		mWalkTransition = false;
		mWait = true;
		mWaitTimer = 0;
	}
}

void Enemy::shortYStepBack()
{
	if (mRect.top > mLastRect.top)
	{
		mRect.top--;
		mLastRect.top--;
	}

	else if (mRect.top < mLastRect.top)
	{
		mRect.top++;
		mLastRect.top++;
	}
}

void Enemy::tick(Entity *player, std::vector<Entity*> entityVector)
{
	if (mActive)
	{
		mLastRect = mRect;
		if(!mControlled)
		{
			if (mCurrentForm == ROOF && mNextForm == ROOF)
			{
				toggleRoofStance();
			}
			if (mRect.top != mOriginalPosition.top)
			{
				if (!mTeleport)
				{
					mTeleport = true;
					mTeleportTimer = 0;
				}
			}
			else
			{
				mTeleport = false;
			}

			if (!mEatWait && !mIdle)
			{
				for (auto i:entityVector)
				{
					if ((i->getTypeID() == 21 && mTypeID == 22) || (i->getTypeID() == 22 && mTypeID == 21))
					{
						checkSight(i);
					}
				}
				checkSight(player);
			}

			if (mRect.left <= mTargetX + 5 && mRect.left >= mTargetX - 5)
			{
				if (mSearching)
				{
					mSearching = false;
				}
				if (!mWait)
				{
					mWalkTransition = true;
					mAnimationTimer = 0;
				}

				mHunting = false;
				mWait = true;
				if (!mTeleport)//Patrullerar inte om den ska teleportera, d� jagar den spelaren eller st�r still
				{
					if (mTargetX == mPatrolStart)
						mTargetX = mPatrolStop;
					else
						mTargetX = mPatrolStart;
				}
			}

			//if (mWait && mNextForm != ROOF && !(mRect.left <= mTargetX + 5 && mRect.left >= mTargetX - 5))
			if (mWait && mNextForm != ROOF)
			{
				mMove = false;
				mWaitTimer++;
				if (mWaitTimer >= mWaitTime)
				{
					if (mRect.left <= mTargetX + 5 && mRect.left >= mTargetX - 5)
					{
						mDirection = mOriginalDirection;
					}
					else
					{
						mWalkTransition = true;
						mAnimationTimer = 0.0f;
						mWait = false;
						mWaitTimer = 0;
					}
				}
			
			}
			else if (mNextForm != EAT && mNextForm != ROOF)
			{
				if(mTargetX < mRect.left)
				{
					if (mHunting)
						mRect.left -= mHuntingSpeed;
					else if (mSearching)
						mRect.left -= mChasingSpeed;
					else
						mRect.left -= mMaxSpeed;
					mDirection = LEFT;
					mMove = true;
				}
				else if(mTargetX > mRect.left)
				{
					if (mHunting)
						mRect.left += mHuntingSpeed;
					else if (mSearching)
						mRect.left += mChasingSpeed;
					else
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
					mWaitTimer = 0;
				}
			}

			if (mEatWaitTimer >= mEatWaitTime)
			{
				mEatWait = false;
				mEatWaitTimer = 0;
			}
			else
			{
				mEatWaitTimer++;
			}
		}

		else
		{
			if (mMove && (mNextForm != ROOF || mCurrentForm == ROOF) && (mCurrentForm != EAT && mNextForm != EAT))
			{
				if (mDirection == LEFT)
				{
					
						mRect.left -= mControlledSpeed;
				}
				else
				{
					mRect.left += mControlledSpeed;
				}
			}
		}

		if (mTypeID == 21)
			setAnimation();
		else
		{
			if (mMove)
				mAnimationY = 1;
			else
				mAnimationY = 3;
			if (mAnimationTimer > mAnimationPicX - mAnimationSpeed)
			{
				mAnimationTimer = 0;
			}
			else
				mAnimationTimer += mAnimationSpeed;
		}


	if(player->getRect().top+100 >= mRect.top && player->getRect().top-100 <= mRect.top)
	{
		mWalkNotSlimeSound.setPosition(mRect.left-player->getRect().left,0,0);
		mWalkSound.setPosition(mRect.left-player->getRect().left,0,0);
	}else
	{
		mWalkNotSlimeSound.setPosition(mRect.left-player->getRect().left,999999,0);
		mWalkSound.setPosition(mRect.left-player->getRect().left,999999,0);
	}
	if(mMove)
	{
		if(mWalkSound.getStatus() != sf::Sound::Playing && mWalkNotSlimeSound.getStatus() != sf::Sound::Playing)
		{
			if(mCurrentForm == form::SLIME || mCurrentForm == form::ROOF)
				mWalkSound.play();
			else
				mWalkNotSlimeSound.play();
		}
		}else
		{
			mWalkSound.stop();
			mWalkNotSlimeSound.stop();
		}

	}

}

void Enemy::setAnimation()
{
	if (mCurrentForm == mNextForm)
	{
		if (getCanSeePlayer() && mCurrentForm == ROOF)
		{
			toggleRoofStance();
		}
		else if (getCanSeePlayer() && mCurrentForm == SLIME)
		{
			mAnimationPicX = 4;
			mAnimationY = 6;
			mAnimationTimer = 0.0f;
			mNextForm = MONSTER;
			if(mMorphSound.getStatus() != sf::Sound::Playing)
			{
				mMorphSound.setPosition(mRect.left-mPlayerX,0,0);
				mMorphSound.play();
			}
		}
		else if (!mSearching && mCurrentForm == MONSTER)
		{
			mNextForm = SLIME;
			mAnimationPicX = 4;
			mAnimationTimer = mAnimationPicX - mAnimationSpeed;
			mAnimationY = 6;
			if(mMorphSound.getStatus() != sf::Sound::Playing)
			{
				mMorphSound.setPosition(mRect.left-mPlayerX,0,0);
				mMorphSound.play();
			}
		}
		else
		{
			if (mCurrentForm == SLIME || mCurrentForm == ROOF)
			{
				if (mWalkTransition)
				{
					mAnimationPicX = 1;
					mAnimationY = 7;
					if(mAnimationTimer >= mAnimationPicX - mAnimationSpeed)
					{
						mAnimationTimer = 0.0f;
						mWalkTransition = false;
					}
					else
						mAnimationTimer += mAnimationSpeed;
				}
				else
				{
					mAnimationPicX = 4;
					mAnimationY = 6;
					if (mMove)
					{
						mAnimationY = 5;
					}
					else
					{
						mAnimationY = 4;
					}

					if(mAnimationTimer >= mAnimationPicX - mAnimationSpeed)
					{
						mAnimationTimer = 0.0f;
					}
					else
						mAnimationTimer += mAnimationSpeed;
				}
			}
			else
			{
				if(mAnimationTimer >= mAnimationPicX - mAnimationSpeed)
				{
					mAnimationTimer = 0.0f;
					if (mCurrentForm == EAT)
					{
						mNextForm = MONSTER;
						mEatWait = true;
						mWait = true;
						mWaitTimer = 0;
					}
				}
				else
					mAnimationTimer += mAnimationSpeed;
			}
		}
	}
	else
	{
		if (mNextForm == ROOF && mCurrentForm != ROOF)
		{
			if (mCurrentForm == ROOFCHANGING)
			{
				if(mAnimationTimer >= mAnimationPicX - mAnimationSpeed)
				{
					mAnimationTimer = 0;
					mCurrentForm = ROOFTRAVEL;
					mAnimationY = 1;
				}
				else
				{
					mAnimationTimer += mAnimationSpeed;
				}
			}
			if (mCurrentForm == ROOFTRAVEL)
			{
				if(mAnimationTimer >= mAnimationPicX - mAnimationSpeed)
					mAnimationTimer = 0;
				else
					mAnimationTimer += mAnimationSpeed;
				if (!mUpsidedown)
				{
					mRect.top -= mFlightSpeed;
				}
				else
				{
					mRect.top += mFlightSpeed;
				}
			}
			if (mCurrentForm == ROOFCHANGINGBACK)
			{
				if(mAnimationTimer <= 0)
				{
					mAnimationTimer = 0;
					if (mUpsidedown)
						mCurrentForm = ROOF;
					else
					{
						mCurrentForm = SLIME;
						mNextForm = SLIME;
					}
					mAnimationY = 4;
				}
				else
					mAnimationTimer -= mAnimationSpeed;
			}
		}
		else if (mCurrentForm == MONSTER && mNextForm == SLIME)
		{

			if(mAnimationTimer <= 0)
			{
				mAnimationTimer = 0.0f;
				mCurrentForm = SLIME;
				mAnimationPicX = 4;
			}
			else
				mAnimationTimer -= mAnimationSpeed;
		}
		else if (mCurrentForm == SLIME)
		{
			
			if(mAnimationTimer >= mAnimationPicX - mAnimationSpeed)
			{

				mAnimationTimer = 0.0f;
				mCurrentForm = mNextForm;
				if (mNextForm == MONSTER)
				{
					mAnimationY = 3;
				}
				else
				{
					mAnimationY = 2;
				}
				mAnimationPicX = 6;

			}
			else
				mAnimationTimer += mAnimationSpeed;
		}
		else if (mNextForm == EAT)
		{
			mAnimationY = 2;
			mAnimationTimer = 0.0f;
			mCurrentForm = mNextForm;
		}
		else if (mNextForm == MONSTER)
		{
			mAnimationY = 3;
			mAnimationTimer = 0.0f;
			mCurrentForm = mNextForm;
		}
	}
}

void Enemy::render(sf::RenderTexture* window, bool visualizeValues, bool mirror, bool upsidedown)
{
	if (mActive)
	{
		
		
		if (mTypeID == 21)
		{
			if (mUpsidedown)
			{
				if(mDirection == RIGHT)
					r.setTextureRect(sf::IntRect(mRect.width * (int)mAnimationTimer, mRect.height * (mAnimationY + 1), mRect.width, -mRect.height));
				else if(mDirection == LEFT)
					r.setTextureRect(sf::IntRect(mRect.width * ((int)mAnimationTimer+1), mRect.height * (mAnimationY + 1), -mRect.width, -mRect.height));
			}
			else
			{
				if(mDirection == RIGHT)
					r.setTextureRect(sf::IntRect(mRect.width * (int)mAnimationTimer, mRect.height * mAnimationY, mRect.width, mRect.height));
				else if(mDirection == LEFT)
					r.setTextureRect(sf::IntRect(mRect.width * ((int)mAnimationTimer+1), mRect.height * mAnimationY, -mRect.width, mRect.height));
			}
		}
		else
		{
			if (mDirection == RIGHT)
				r.setTextureRect(sf::IntRect(mRect.width * ((int)mAnimationTimer + 1), mRect.height * mAnimationY, -mRect.width, mRect.height));
			else
				r.setTextureRect(sf::IntRect(mRect.width * (int)mAnimationTimer, mRect.height * mAnimationY, mRect.width, mRect.height));
		}
		r.setPosition(mRect.left,mRect.top);
		
	
		/*mWindow->clear(sf::Color(255, 0, 255));
		mWindow->draw(mText);
		mWindow->display();*/
		window->draw(r);
	}
	/*sf::RectangleShape r;
	r.setTexture(mTexture);
	r.setTextureRect(sf::IntRect(mRect.width,0,-mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);*/

	if (visualizeValues)
	{
		sf::RectangleShape aggroRangeLine(sf::Vector2f(mAggroRange, 2));
		aggroRangeLine.setFillColor(sf::Color::White);
		if (mDirection == RIGHT)
			aggroRangeLine.setPosition(mRect.left, mRect.top);
		else
			aggroRangeLine.setPosition(mRect.left - mAggroRange, mRect.top);

		sf::RectangleShape viewFrontRangeLine(sf::Vector2f(mViewFrontRange, 2));
		viewFrontRangeLine.setFillColor(sf::Color::Red);
		if (mDirection == RIGHT)
			viewFrontRangeLine.setPosition(mRect.left, mRect.top+10);
		else
			viewFrontRangeLine.setPosition(mRect.left - mViewFrontRange, mRect.top+10);

		sf::RectangleShape viewBackRangeLine(sf::Vector2f(mViewBackRange, 2));
		viewBackRangeLine.setFillColor(sf::Color::Green);
		if (mDirection == RIGHT)
			viewBackRangeLine.setPosition(mRect.left - mViewBackRange, mRect.top+20);
		else
			viewBackRangeLine.setPosition(mRect.left, mRect.top+20);

		sf::CircleShape startTriangle(10, 3);
		startTriangle.setPosition(mPatrolStart, mRect.top);

		sf::CircleShape stopTriangle(10, 3);
		stopTriangle.setPosition(mPatrolStop, mRect.top);

		sf::CircleShape targetSquare(10, 3);
		targetSquare.setFillColor(sf::Color::Blue);
		targetSquare.setPosition(mTargetX, mRect.top);

		window->draw(aggroRangeLine);
		window->draw(viewFrontRangeLine);
		window->draw(viewBackRangeLine);
		window->draw(startTriangle);
		window->draw(stopTriangle);
		window->draw(targetSquare);
	}
}

void Enemy::flashlight(bool flash)
{
}

void Enemy::setImortal(bool imortal)
{
	mImortal = imortal;
}

bool Enemy::getImortal()
{
	return mImortal;
}

void Enemy::setIdle()
{
	mIdle = true;
}