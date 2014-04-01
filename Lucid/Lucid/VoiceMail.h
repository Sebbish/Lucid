#ifndef VOICEMAIL_H
#define VOICEMAIL_H
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
class VoiceMail
{
public:
	struct mSoundSlot {
	public:
		mSoundSlot(std::string title, std::string soundPath,std::string text)
		{
			mTitle = title;
			mSound.openFromFile("../../../LucidProject/Resources/Sound/voicemail/"+soundPath+".ogg");
			mUsed = false;
			mText = text;
		}
		std::string mTitle;
		sf::Music mSound;
		std::string mText;
		bool mUsed;
	};

	VoiceMail(int mapID,sf::Texture* Voicemail);
	~VoiceMail();
	void newMap(int mapID);
	void playNextSound();
	void playSound(int ID);
	void stop();
	int getActiveSoundID();
	void nextPrevSoundSlot(bool next);
	void activateNextSound(bool play);
	std::vector<mSoundSlot*> getSounds();
	void tick();
	void render(sf::RenderWindow *target);
private:
	void loadSounds(int mapID);
	bool mDraw;
	int mActiveSoundID;
	int mSoundPlayingID;
	std::vector<mSoundSlot*> mSounds;
	std::vector<mSoundSlot*> mActiveSounds;
	sf::Texture *mTexture;
	sf::Font mFont;
	sf::Text mText;
	sf::RectangleShape mRS;
};
#endif

