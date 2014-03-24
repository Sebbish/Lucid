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
	virtual sf::FloatRect getHitBox()const;
	virtual bool getShowE();
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
	virtual int getFunc(Entity* player);
private:
	sf::FloatRect mRect;
	sf::FloatRect rectSet;
	int mTypeID;
	sf::Texture* mTexture;
};

#endif
