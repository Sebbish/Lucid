#ifndef CAMERA_H
#define CAMERA_H
#include "SFML\Graphics.hpp"
#include "Entity.h"
class Camera
{
public:
	Camera(Entity* CameraFollowThisEntity);
	~Camera();
	void tick();
private:
	sf::View mView;
	Entity* mFollowThisEntity;
};
#endif

