#ifndef MOBIL_H
#define MOBIL_H
#include "SFML\Graphics.hpp"
#include "vector"
#include "SaveLoad.h"
#include "snake.h"
#include "VoiceMail.h"
#include "VoiceDialog.h"
#include <iostream>
class Mobil
{
public:
	Mobil(sf::Texture* texture,sf::Texture* lines,int mapID,sf::Texture* Voicemail,sf::Vector2u windowSize);
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
	void nextSound();
	void nextDialog();
	int getDialogID();
	void VoiceMailTick();
	void VoiceMailRender(sf::RenderWindow *target);
	bool slutPÂTest;
	bool getMC;
	void setCurrentLevel(int lvl);
	int getCurrentLevel();
private:
	void save();
	bool mVoiceMail;
	bool mVoiceMail2;
	void ActivateSnakes();
	void ActivateSnakesAI();
	sf::Texture* mTexture;
	sf::Texture* mLines;
	sf::FloatRect mRect;
	sf::FloatRect mApp[10];
	sf::Font f;
	sf::RectangleShape rs;
	sf::Text t;

	bool mActivated;
	int mActiveAppID;
	snake *s;
	VoiceMail *mVM;
	VoiceDialog *mVD;
	sf::Vector2f firstMenuThing;
	float textH;
	float textY;
	int mcurrentLevel;

};
#endif

