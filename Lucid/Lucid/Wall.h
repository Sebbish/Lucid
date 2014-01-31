#ifndef WALL_H
#define WALL_H

#include "object.h"

class Wall :
	public Object
{
public:
	Wall(sf::FloatRect rect);
	~Wall();
	virtual sf::FloatRect getRect()const;
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
	virtual void getFunc(Entity* player);
private:
	sf::FloatRect mRect;
};

#endif