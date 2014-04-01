#ifndef VOICEDIALOG_H
#define VOICEDIALOG_H
#include <string>
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
#include <vector>
class VoiceDialog
{
public:
	struct mSoundSlot {
	public:
		mSoundSlot(std::string soundPath,std::string text)
		{
			
			mSound.openFromFile("LucidProject/Resources/Sound/Dialog/"+soundPath+".ogg");
			mText = text;
		}
		sf::Music mSound;
		std::string mText;
	};
	VoiceDialog(sf::Texture *t);
	~VoiceDialog();
	void newLevel(int mapID);
	void playNextDialog();
	void playDialog(int id);
	int getDialogID();
	void boatLvl8Thing();
	bool playingLvl8Thing();
	void tick();
	void render(sf::RenderWindow *target);
private:
	std::vector<mSoundSlot*> mSounds;
	int playingSoundID;
	sf::Texture *mTexture;
	sf::Font mFont;
	sf::Text mText;
	sf::RectangleShape mRS;
	bool mDraw;
	int mMapID;
	float pause;
	bool lvl8Thing;
};
#endif

