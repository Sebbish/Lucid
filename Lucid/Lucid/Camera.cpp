#include "Camera.h"

Camera::Camera(sf::Vector2f size,Entity *CameraFollowThisEntity):
	mFollowThisEntity(CameraFollowThisEntity)
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
	float tempX = dataVector[18];
	float tempY = dataVector[20];
	float tempAcceleration = dataVector[22];
	acc = tempAcceleration / 1000;
	accY = 0.2;
	mView.setSize(sf::Vector2f(tempX, tempY));
	mOriginalSize = sf::Vector2f(tempX, tempY);
	mZoom = false;

	//mView.setCenter(sf::Vector2f(mFollowThisEntity->getRect().left+(mView.getSize().x/2)/6*2,mFollowThisEntity->getRect().top+mFollowThisEntity->getRect().height/2));

	mView.setCenter((mFollowThisEntity->getRect().left + mFollowThisEntity->getRect().width / 2) + (mView.getSize().x / 6), mFollowThisEntity->getRect().top+mFollowThisEntity->getRect().height/2 + 44);

	//mView.setSize(size);
	//mView.setSize(sf::Vector2f(1920,1080));
}


Camera::~Camera(void)
{
}

void Camera::moveCameraPosition(sf::Vector2f &position)
{
	mView.setCenter(mView.getCenter().x+position.x,mView.getCenter().y-position.y);
}

void Camera::tick()
{
	
	/*if (mZoom)
	{
		if (mView.getSize().x > mOriginalSize.x * 0.9)
			mView.zoom(0.99);
	}
	else
	{
		if (mView.getSize().x < mOriginalSize.x)
		{
			mView.zoom(1.01);
		}
		else
		{
			mView.setSize(mOriginalSize);
		}
	}*/

	float playerpos = mFollowThisEntity->getRect().left + mFollowThisEntity->getRect().width / 2;
	float distance = mView.getSize().x / 6;
	float targetPos;
	if (mFollowThisEntity->getDirection() == Entity::RIGHT)
	{
		targetPos = playerpos + distance;
	}
	else
	{
		targetPos = playerpos - distance;
	}
	float currentPos = mView.getCenter().x;
	float move = (targetPos - currentPos) * acc;

	float targetPosY = mFollowThisEntity->getRect().top + mFollowThisEntity->getRect().height / 2 + 44;
	float currentPosY = mView.getCenter().y;
	float moveY = (targetPosY - currentPosY) * accY;

	//mView.setCenter(currentPos + move, mFollowThisEntity->getRect().top+mFollowThisEntity->getRect().height/2 + 44);
	mView.setCenter(currentPos + move, currentPosY + moveY);

	/*if(mFollowThisEntity->getDirection() == Entity::RIGHT)
	{
		float distance = ((mFollowThisEntity->getRect().left+mFollowThisEntity->getRect().width/2)-(mView.getCenter().x-mView.getSize().x/6))*acc;
		mView.setCenter(mView.getCenter().x+distance,mFollowThisEntity->getRect().top+mFollowThisEntity->getRect().height/2 + 44);
			
	}else if(mFollowThisEntity->getDirection() == Entity::LEFT)
	{
		float distance = ((mFollowThisEntity->getRect().left+mFollowThisEntity->getRect().width/2)-(mView.getCenter().x+mView.getSize().x/6))*acc;
		mView.setCenter(mView.getCenter().x+distance,mFollowThisEntity->getRect().top+mFollowThisEntity->getRect().height/2 + 44);
	}*/

	
}

sf::View* Camera::getView()
{
	return &mView;
}

void Camera::setTarget(Entity *entity)
{
	mFollowThisEntity = entity;
	float playerpos = mFollowThisEntity->getRect().left + mFollowThisEntity->getRect().width / 2;
	float distance = mView.getSize().x / 6;
	float targetPos;
	if (mFollowThisEntity->getDirection() == Entity::RIGHT)
	{
		targetPos = playerpos + distance;
	}
	else
	{
		targetPos = playerpos - distance;
	}
	mView.setCenter(targetPos, mFollowThisEntity->getRect().top+mFollowThisEntity->getRect().height/2 + 44);
}

void Camera::zoom(bool zoom)
{
	mZoom = zoom;
}