#include "Camera.h"

float acc = 0.1f;

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
	mView.setSize(sf::Vector2f(tempX, tempY));
	mOriginalSize = sf::Vector2f(tempX, tempY);
	mZoom = false;

	mView.setCenter(sf::Vector2f(mFollowThisEntity->getRect().left+(mView.getSize().x/2)/6*2,mFollowThisEntity->getRect().top+mFollowThisEntity->getRect().height/2));
	//mView.setSize(size);
	//mView.setSize(sf::Vector2f(1920,1080));
}


Camera::~Camera(void)
{
}

void Camera::tick()
{
	
	if (mZoom)
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
	}

	if(mFollowThisEntity->getDirection() == Entity::RIGHT)
	{
		float distance = ((mFollowThisEntity->getRect().left+mFollowThisEntity->getRect().width/2)-(mView.getCenter().x-mView.getSize().x/6))*acc;
		mView.setCenter(mView.getCenter().x+distance,mFollowThisEntity->getRect().top+mFollowThisEntity->getRect().height/2);
			
	}else if(mFollowThisEntity->getDirection() == Entity::LEFT)
	{
		float distance = ((mFollowThisEntity->getRect().left+mFollowThisEntity->getRect().width/2)-(mView.getCenter().x+mView.getSize().x/6))*acc;
		mView.setCenter(mView.getCenter().x+distance,mFollowThisEntity->getRect().top+mFollowThisEntity->getRect().height/2);
	}

	
}

sf::View* Camera::getView()
{
	return &mView;
}

void Camera::setTarget(Entity *entity)
{
	mFollowThisEntity = entity;
}

void Camera::zoom(bool zoom)
{
	mZoom = zoom;
}