#include "Enemy.h"


Enemy::Enemy(float x, float y, float width, float height,float speed, int direction, int patrolStart, int patrolStop, sf::Texture* texture, int typeID, int active, sf::SoundBuffer* walkSound,sf::SoundBuffer* jagaSound):
	mMaxSpeed(speed), mTexture(texture),mMove(false), mTypeID(typeID),mTempCollideWithPlayer(false),mControlled(false), mPatrolStart(patrolStart), mPatrolStop(patrolStop)
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
	if (mTypeID == 21)
	{
		mMaxSpeed = dataVector[2];
		mHuntingSpeed = 8;
	}
	else
	{
		mMaxSpeed = dataVector[4];
		mHuntingSpeed = 4;
	}
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
	}
	else
	{
		mDirection = RIGHT;
	}
	mAnimationPicX = 4;
	mLayer = Front;
	mAnimationTimer = 0;
	mWaitTimer = 0;
	mWait = false;
	//mWaitTime = 60;
	/*mViewBackRange = 300;
	mViewFrontRange = 800;
	mAggroRange = 400;*/
	mIsPlayerVisible = false;
	mTargetX = mPatrolStop;
	mWalkSound.setBuffer(*walkSound);
	mJagaSound.setBuffer(*jagaSound);
	mTeleportWaitTime = 300;
	mTeleport = false;
	mTeleportTimer = 0;
	if (active == 0)
		mActive = false;
	else
		mActive = true;

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
	if (mActive)
	{
		if (entity->getTypeID() == 22 && mTypeID == 21)
		{
			mRect.left = -5000;
			mRect.top = -5000;
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

sf::FloatRect Enemy::getLastRect()const
{
	return mLastRect;
}

void Enemy::setRect(sf::FloatRect rect)
{
	mRect = rect;
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
					mTargetX += mAggroRange;
				}
				else
				{
					mTargetX -= mAggroRange;
				}
				mIsPlayerVisible = true;
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
	}
	/*else
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
	}*/
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

void Enemy::tick(Entity *player, std::vector<Entity*> entityVector)
{
	if (mActive)
	{
		mLastRect = mRect;
		if(!mControlled)
		{
			if (mRect.top != mOriginalPosition.top)
			{
				mTeleport = true;
			}
			for (auto i:entityVector)
			{
				if (i->getTypeID() == 21 && mTypeID == 22)
				{
					checkSight(i);
				}
			}
			checkSight(player);
		

			if (mRect.left <= mTargetX + 5 && mRect.left >= mTargetX - 5)
			{
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
					if (mHunting)
						mRect.left -= mHuntingSpeed;
					else
						mRect.left -= mMaxSpeed;
					mDirection = LEFT;
					mMove = true;
				}
				else if(mTargetX > mRect.left)
				{
					if (mHunting)
						mRect.left += mHuntingSpeed;
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
		}

		else
		{
			if (mMove)
			{
				if (mDirection == LEFT)
				{
					
						mRect.left -= mHuntingSpeed;
				}
				else
				{
					mRect.left += mHuntingSpeed;
				}
			}
		}

		if(mMove)
			{
				if(mAnimationTimer >= mAnimationPicX - 0.1f)
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
	mWalkSound.setMinDistance(1000);
	mWalkSound.setAttenuation(10);
	if(player->getRect().top+100 >= mRect.top && player->getRect().top-100 <= mRect.top)
		mWalkSound.setPosition(mRect.left-player->getRect().left,0,0);
	else
		mWalkSound.setPosition(mRect.left-player->getRect().left,999999,0);
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

}

void Enemy::render(sf::RenderTexture* window, bool visualizeValues)
{
	if (mActive)
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