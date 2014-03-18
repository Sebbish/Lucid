#ifndef CAMERA_H
#define CAMERA_H
#include "SFML\Graphics.hpp"
#include "Entity.h"
class Camera
{
public:
	Camera(sf::Vector2f size,Entity *CameraFollowThisEntity);
	~Camera();
	void tick();
	sf::View* getView();
	void setTarget(Entity *entity);
	void zoom(bool zoom);
private:
	sf::View mView;
	Entity* mFollowThisEntity;
	Entity::direction EntityDirection;
	bool mZoom;
	sf::Vector2f mOriginalSize;
	float acc, accY;
};
#endif

