#include "Camera.h"

float acc = 0.1f;

Camera::Camera(sf::Vector2f size,Entity *CameraFollowThisEntity):
	mFollowThisEntity(CameraFollowThisEntity)
{
	mView.setCenter(sf::Vector2f(mFollowThisEntity->getRect().left+(mView.getSize().x/2)/6*2,size.y/2));
	mView.setSize(size);
}


Camera::~Camera(void)
{
}

void Camera::tick()
{
	
	if(mFollowThisEntity->getDirection() == Entity::RIGHT)
	{
		float distance = ((mFollowThisEntity->getRect().left+mFollowThisEntity->getRect().width/2)-(mView.getCenter().x-mView.getSize().x/6))*acc;
		mView.setCenter(mView.getCenter().x+distance,mView.getCenter().y);
			
	}else if(mFollowThisEntity->getDirection() == Entity::LEFT)
	{
		float distance = ((mFollowThisEntity->getRect().left+mFollowThisEntity->getRect().width/2)-(mView.getCenter().x+mView.getSize().x/6))*acc;
		mView.setCenter(mView.getCenter().x+distance,mView.getCenter().y);
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
