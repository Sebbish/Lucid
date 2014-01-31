#ifndef HIDING_H
#define HIDING_H

#include "object.h"

class Hiding :
	public Object
{
public:
	Hiding(sf::FloatRect rect, sf::Texture* texture, int typeID);
	~Hiding();
	virtual sf::FloatRect getRect()const;
	virtual void tick();
	virtual void render(sf::RenderWindow* window);
	virtual void getFunc(Entity* player);
private:
	sf::FloatRect mRect;
	int mTypeID;
	sf::Texture* mTexture;
};

#endif
