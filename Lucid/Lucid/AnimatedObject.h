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
		InFrontOfObjects,
		BehindBackground
	};
	enum AnimationDirection
	{
		Forward,
		Backward
	};
	AnimatedObject(sf::FloatRect rect, sf::Texture* texture, int typeID, int active, int layer, int animationY, int animationPicX, int direction, int alpha, int animate, int loop);
	~AnimatedObject(void);
	virtual sf::FloatRect getRect()const;
	virtual sf::FloatRect getHitBox()const;
	virtual int getFunc(Entity* player);
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
	void setActive(bool acive);
	Layer getLayer();
	int getAlpha();
	void setAlpha(int alpha);
	void setAnimate(bool animate);
	void setLoop(bool loop);
	void fadeout();
	void fadein();
private:
	sf::FloatRect mRect;
	int mTypeID;
	sf::Texture* mTexture;
	bool mActive;
	Layer mLayer;
	int mAlpha;
	float mAnimationTimer;
	int mAnimationPicX;
	int mAnimationY;
	float mAnimationSpeed;
	bool mAnimate;
	bool mLoop;
	AnimationDirection mAnimationDirection;
	bool mFadeIn, mFadeOut;
	int mFadeSpeed;
	sf::RectangleShape r;
};

#endif
