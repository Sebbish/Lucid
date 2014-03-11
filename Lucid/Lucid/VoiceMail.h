#ifndef VOICEMAIL_H
#define VOICEMAIL_H
#include "SFML\Audio.hpp"
#include <vector>
#include <string>
#include <iostream>
class VoiceMail
{
public:
	struct mSoundSlot {
	public:
		mSoundSlot(std::string title, std::string soundPath)
		{
			mTitle = title;
			mSound.openFromFile(soundPath);
			mUsed = false;
		}
		std::string mTitle;
		sf::Music mSound;
		std::string mText;
		bool mUsed;
	};

	VoiceMail(int mapID);
	~VoiceMail();
	void newMap(int mapID);
	void playNextSound();
	void playSound(int ID);
	void stop();
	int getActiveSoundID();
	void nextPrevSoundSlot(bool next);
	void activateNextSound();
	std::vector<mSoundSlot*> getSounds();
private:
	void loadSounds(int mapID);

	int mActiveSoundID;
	std::vector<mSoundSlot*> mSounds;
	std::vector<mSoundSlot*> mActiveSounds;
};
#endif

