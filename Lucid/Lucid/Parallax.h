#ifndef PARALLAX_H
#define PARALLAX_H
#include "object.h"
#include "Camera.h"
class Parallax :
	public Object
{
public:
	Parallax(sf::FloatRect rect, sf::Texture* texture, int typeID, Camera* camera);
	~Parallax(void);
	virtual sf::FloatRect getRect()const;
	virtual int getFunc(Entity* player);
	virtual void tick();
	virtual void render(sf::RenderTexture* window);
private:
	sf::FloatRect mRect;
	int mTypeID;
	sf::Texture* mTexture;
	Camera* mCamera;
	int mOriginX;
	float mVariabel;
};

#endif