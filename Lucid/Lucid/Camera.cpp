#include "Camera.h"

float acc = 0.1f;

Camera::Camera(sf::Vector2f size,Entity* CameraFollowThisEntity):
	mFollowThisEntity(CameraFollowThisEntity)
{
	mView.setCenter(sf::Vector2f(mFollowThisEntity->getRect().left+(mView.getSize().x/2)/6*2,mFollowThisEntity->getRect().top));
	mView.setSize(size);
}


Camera::~Camera(void)
{
}

void Camera::tick()
{
	if(mFollowThisEntity->getDirection() == Entity::RIGHT)
	{
		
			//mView.setCenter(sf::Vector2f(mFollowThisEntity->getRect().left+(mView.getSize().x/2)/6*2,mFollowThisEntity->getRect().top));
	}else if(mFollowThisEntity->getDirection() == Entity::LEFT)
	{
		
			//mView.setCenter(sf::Vector2f(mFollowThisEntity->getRect().left-(mView.getSize().x/2)/6*2,mFollowThisEntity->getRect().top));
	}
}

sf::View* Camera::getView()
{
	return &mView;
}
