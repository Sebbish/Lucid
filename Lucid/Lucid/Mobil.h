#ifndef MOBIL_H
#define MOBIL_H
#include "SFML\Graphics.hpp"
#include "vector"
#include "SaveLoad.h"
class Mobil
{
public:
	Mobil(sf::Texture* texture,SaveLoad* SL, int mapID);
	~Mobil();
	void activate(sf::View* view,int mapID);
	void deactivate();
	void nextApp();
	void lastApp();
	int getActiveAppID();
	bool getActivate()const;
	void tick();
	void render(sf::RenderWindow* target);
	void save(int mapID);
	bool getSkriver()const;
	void addTextToSaveSlot(char tecken);
	bool IWantToLoad();
	void setWritingText(bool text);
	void reset();
private:
	void save();

	sf::Texture* mTexture;
	sf::FloatRect mRect;
	sf::FloatRect mApp[10];

	bool mActivated;
	bool mLoad;
	bool mSave;
	bool mSkriverSaveSlotText;
	int mActiveAppID;
	int mMapID;
	std::string mSaveName;

	SaveLoad* mSL;
};
#endif

