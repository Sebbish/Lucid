#ifndef MOBIL_H
#define MOBIL_H
#include "SFML\Graphics.hpp"
#include "vector"
#include "SaveLoad.h"
#include "snake.h"
class Mobil
{
public:
	Mobil(sf::Texture* texture,sf::Texture* lines);
	~Mobil();
	void activate(sf::View* view);
	void deactivate();
	void nextApp();
	void lastApp();
	int getActiveAppID();
	bool getActivate()const;
	void tick();
	void render(sf::RenderWindow& target);
	void reset();
	bool snakes;
private:
	void save();

	void ActivateSnakes();
	sf::Texture* mTexture;
	sf::Texture* mLines;
	sf::FloatRect mRect;
	sf::FloatRect mApp[10];

	bool mActivated;
	int mActiveAppID;
	snake *s;

};
#endif

