#include "Cube.h"


Cube::Cube(sf::FloatRect& rec,bool leader,bool fruit,sf::Texture& t,sf::FloatRect maxSize):
	mLeader(leader),mFruit(fruit),t(t)
{
	mRect = rec;
	this->maxSize = maxSize;
	mD = RIGHT;
	mNextD = RIGHT;
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

void Cube::render(sf::RenderWindow& target)
{
	

	sf::RectangleShape rs;
	rs.setPosition(mRect.left,mRect.top);
	rs.setSize(sf::Vector2f(mRect.width,mRect.height));
	rs.setTexture(&t);
	target.draw(rs);
}
