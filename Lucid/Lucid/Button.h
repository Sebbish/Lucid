#ifndef BUTTON_H
#define BUTTON_H

#include "SFML\Graphics.hpp"
#include "Object.h"
#include "Camera.h"

class Button
{
public:
	Button(sf::Texture* texture);
	~Button(void);
	void render(sf::RenderWindow* window, Camera* camera);
	void setObject(Object* object);
	void willRender(bool render);
	bool getRender();
private:
	sf::Clock mClock;
	sf::Texture* mTexture;
	Object* mObject;
	bool mWillRender;
};

#endif