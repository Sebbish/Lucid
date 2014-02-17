#ifndef LIGHT_SOURCE_H
#define	LIGHT_SOURCE_H
#include <SFML\Graphics.hpp>
#include <fstream>
#include <string>
#include "Entity.h"
#include "Light.h"
#include "LightManager.h"

class LightSource
{
public:
	enum directionLight {
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	virtual ~LightSource() = 0;
	virtual sf::FloatRect getRect()const =0;
	virtual db::Light* render() = 0;
	virtual void setRect(sf::FloatRect rect) = 0;
	virtual void setPosition (sf::FloatRect rect) = 0;
	virtual void setTexture(sf::Texture texture) = 0;
};
#endif
