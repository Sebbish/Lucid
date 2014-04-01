#include "Cube.h"


Cube::Cube(sf::FloatRect& rec,bool leader,bool fruit,sf::Texture& t,sf::FloatRect maxSize):
	mLeader(leader),mFruit(fruit),t(t)
{
	mRect = rec;
	this->maxSize = maxSize;
	mD = RIGHT;
	mNextD = RIGHT;
	rs.setSize(sf::Vector2f(mRect.width,mRect.height));
	rs.setTexture(&t);
}


Cube::~Cube()
{
}

void Cube::setDirection(direction d)
{
	switch(d)
	{
	case 0:
		if(mD != 1)
			mNextD = UP;
		break;
	case 1:
		if(mD != 0)
			mNextD = DOWN;
		break;
	case 2:
		if(mD != 3)
			mNextD = LEFT;
		break;
	case  3:
		if(mD != 2)
			mNextD = RIGHT;
		break;
	}
}

sf::FloatRect& Cube::getRect()
{
	return mRect;
}

void Cube::setRect(sf::FloatRect& rect)
{
	mRect = rect;
}


void Cube::tick(sf::FloatRect& rect)
{
	mD = mNextD;
	if(mLeader)
	{
		switch(mD)
		{
		case 0:
			mRect.top -= mRect.height;
			break;
		case 1:
			mRect.top += mRect.height;
			break;
		case 2:
			mRect.left -= mRect.width;
			break;
		case 3:
			mRect.left += mRect.width;
			break;
		}
	}else
	{
		mRect = rect;
	}

	if(mLeader)
	{
		if(mRect.left >= maxSize.left+maxSize.width)
			mRect.left = maxSize.left;

		if(mRect.top >= maxSize.top+maxSize.height)
			mRect.top = maxSize.top;

		if(mRect.top < maxSize.top)
			mRect.top = maxSize.top+maxSize.height-40;

		if(mRect.left < maxSize.left)
			mRect.left = maxSize.left+maxSize.width-40;
	}
}

void Cube::render(sf::RenderWindow& target, int animationX)
{
	/*sf::RectangleShape r;
	r.setTexture(mTexture);
	if(mDirection == RIGHT)
		r.setTextureRect(sf::IntRect(mRect.width*(int)mAnimationTimer, mAnimationY * mRect.height,mRect.width,mRect.height));
	else if(mDirection == LEFT)
		r.setTextureRect(sf::IntRect(mRect.width*((int)mAnimationTimer+1),mAnimationY * mRect.height,-mRect.width,mRect.height));
	r.setPosition(mRect.left,mRect.top);
	r.setSize(sf::Vector2f(mRect.width,mRect.height));
	window->draw(r);*/

	
	if (mLeader)
		rs.setFillColor(sf::Color::Red);
	
	if (animationX != 2)
		rs.setTextureRect(sf::IntRect(animationX * 256, 0, 256, 256));
	rs.setPosition(mRect.left,mRect.top);
	
	
	target.draw(rs);
}
