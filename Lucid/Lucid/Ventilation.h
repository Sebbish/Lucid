#ifndef VENTILATION_H
#define VENTILATION_H

#include "object.h"
class Ventilation :
	public Object
{
public:
	Ventilation(int x, int y, int height);
	~Ventilation(void);
	virtual sf::FloatRect getRect()const;
	virtual sf::FloatRect getHitBox()const;
	virtual bool getShowE();
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
	virtual int getFunc(Entity* player);
private:
	sf::FloatRect mRect;
};

#endif

