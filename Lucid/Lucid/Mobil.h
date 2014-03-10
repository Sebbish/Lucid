#ifndef MOBIL_H
#define MOBIL_H
#include "SFML\Graphics.hpp"
#include "vector"
#include "SaveLoad.h"
#include "snake.h"
#include "VoiceMail.h"
class Mobil
{
public:
	Mobil(sf::Texture* texture,sf::Texture* lines,int mapID);
	~Mobil();
	void activate(sf::RenderWindow* view);
	void deactivate();
	void nextApp();
	void lastApp();
	int getActiveAppID();
	bool getActivate()const;
	void tick();
	void render(sf::RenderWindow& target);
	void reset();
	bool snakes;
	void newMap(int mapID);
private:
	void save();
	bool mVoiceMail;
	void ActivateSnakes();
	void ActivateSnakesAI();
	sf::Texture* mTexture;
	sf::Texture* mLines;
	sf::FloatRect mRect;
	sf::FloatRect mApp[10];

	bool mActivated;
	int mActiveAppID;
	snake *s;
	VoiceMail *mVM;

};
#endif

