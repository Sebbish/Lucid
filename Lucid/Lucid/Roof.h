#pragma once
#include "object.h"
class Roof :
	public Object
{
public:
	Roof(sf::FloatRect rect);
	~Roof(void);
	virtual sf::FloatRect getRect()const;
	virtual int getFunc(Entity* player);
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
private:
	sf::FloatRect mRect;
	bool mActive;
};

