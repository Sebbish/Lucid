#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H
#include "LightSource.h"

class Flashlight : 
	public LightSource
{
public:
	Flashlight(float x, float y,sf::Color color, int onOff, sf::Texture *texture);
	~Flashlight();
	virtual sf::FloatRect getRect()const;
	virtual db::Light* render();
	virtual void setRect(sf::FloatRect rect);
	virtual void setPosition (sf::FloatRect rect);
	virtual void setTexture(sf::Texture texture);
private:
	sf::FloatRect mRect;
	sf::Texture mTexture;
	sf::Color mColor;
	db::Light* mLight;
	bool mOnOff;
};

#endif // !FLASHLIGHT_H
