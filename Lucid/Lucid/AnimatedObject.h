#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H
#include "object.h"
class AnimatedObject :
	public Object
{
public:
	enum Layer
	{
		Foreground,
		BehindObjects,
		InFrontOfObjects
	};
	AnimatedObject(sf::FloatRect rect, sf::Texture* texture, int typeID, int active, int layer);
	~AnimatedObject(void);
	virtual sf::FloatRect getRect()const;
	virtual int getFunc(Entity* player);
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
	void setActive(bool acive);
	Layer getLayer();
	int getAlpha();
	void setAlpha(int alpha);
private:
	sf::FloatRect mRect;
	int mTypeID;
	sf::Texture* mTexture;
	bool mActive;
	Layer mLayer;
	int mAlpha;
};

#endif
