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

	mView.setCenter(sf::Vector2f(mFollowThisEntity->getRect().left+(mView.getSize().x/2)/6*2,mFollowThisEntity->getRect().top+mFollowThisEntity->getRect().height/2));
	//mView.setSize(size);
	mView.setSize(sf::Vector2f(16*100,9*100));
}


Camera::~Camera(void)
{
}

void Camera::tick()
{
	
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
