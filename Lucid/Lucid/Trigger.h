#ifndef TRIGGER_H
#define TRIGGER_H
#include "object.h"

class Trigger :
	public Object
{
public:
	Trigger(sf::FloatRect rect, int triggedByID, int active);
	~Trigger(void);
	virtual sf::FloatRect getRect()const;
	virtual sf::FloatRect getHitBox()const;
	virtual int getFunc(Entity* player);
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
	void setActive(bool active);
	bool getActive();
	bool getTrigged();
private:
	sf::FloatRect mRect;
	bool mTrigged;
	bool mActive;
	int mTriggedByID;
};

#endif