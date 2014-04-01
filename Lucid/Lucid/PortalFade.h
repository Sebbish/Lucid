#ifndef PORTALFADE_H
#define PORTALFADE_H

#include "SFML\Graphics.hpp"

class PortalFade
{
public:
	PortalFade(sf::Texture* texture, sf::RenderTexture &renderTexture);
	~PortalFade(void);
	void render(sf::RenderWindow &window);
	void fadeIn();
	void fadeOut(sf::FloatRect position);
	sf::FloatRect tick();
private:
	int mAlpha;
	bool mFadeIn;
	bool mFadeOut;
	sf::FloatRect mPosition;
	int mFadeSpeed;
	sf::Texture* mTexture;
	sf::Vector2f mSize;
	int mWaitTime;

	sf::RectangleShape r;
};

#endif