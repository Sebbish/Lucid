#ifndef WALL_H
#define WALL_H

#include "object.h"

class Wall :
	public Object
{
public:
	Wall(sf::FloatRect rect, int active);
	~Wall();
	virtual sf::FloatRect getRect()const;
	virtual sf::FloatRect getHitBox()const;
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
	virtual int getFunc(Entity* player);
	void setActive(bool active);
private:
	sf::FloatRect mRect;
	bool mActive;
};

#endif