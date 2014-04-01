#ifndef FADE_H
#define FADE_H

#include "SFML\Graphics.hpp"

class Fade
{
public:
	Fade(sf::Texture* texture, sf::RenderTexture &renderTexture);
	~Fade(void);
	void render(sf::RenderWindow &window);
	void fadeIn();
	void fadeOut(int newMapID);
	int tick();
private:
	int mAlpha;
	bool mFadeIn;
	bool mFadeOut;
	int mMapID;
	int mFadeSpeed;
	sf::Texture* mTexture;
	sf::Vector2f mSize;
	sf::RectangleShape r;
};

#endif