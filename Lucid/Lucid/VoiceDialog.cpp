#include "VoiceDialog.h"


VoiceDialog::VoiceDialog(sf::Texture *t):
	playingSoundID(-1),mTexture(t)
{
	mFont.loadFromFile("../../../LucidProject/Resources/Dialog/ariblk.ttf");
	mText.setFont(mFont);
	mDraw = false;
	mRS.setSize(sf::Vector2f(960,200));
	mRS.setFillColor(sf::Color::White);
	mRS.setTexture(mTexture);
	pause = 0.0;
}


VoiceDialog::~VoiceDialog()
{
	while(mSounds.size() > 0)
	{
		delete mSounds[mSounds.size()-1];
		mSounds.pop_back();
	}
}

void VoiceDialog::newLevel(int mapID)
{
	mMapID = mapID;
	mDraw = false;
	playingSoundID = -1;
	std::string a;
	a = '\n';
	while(mSounds.size() > 0)
	{
		delete mSounds[mSounds.size()-1];
		mSounds.pop_back();
	}
	switch (mapID)
	{
	case 7:
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Taunt_Businesswoman","Hey captain! Nice job breaking"+a+"everything"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Taunt_Moneyback","I demand my money back!"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Taunt_Oldlady","Well hurry up then, boat's not gonna"+a+"steer itself!"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Taunt_Oldman","Do something! You're the captain"+a+"right?!"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Taunt_MrGreen","Are….are we going to die?"));

		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Texasman_1","Look son, there goes the captain,"+a+"what a sorry sight to see right?"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Pojkvasker_1","But you said captains are super cool"+a+"guys who get to use that big steering"+a+"wheel. "));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Texasman_2","Well most of them are, this one is just"+a+"a big lazy bum though."));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Pojkvasker_2","Dad?"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Texasman_3","Yes?"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Pojkvasker_3","I don't want to be a captain when I"+a+"grow up, I think it looks hard and you"+a+"will just get sad like him"));
		break;
	default:
		break;
	}

}

void VoiceDialog::playNextDialog()
{
	playingSoundID++;
	if(playingSoundID <= mSounds.size()-1)
	{
		mSounds[playingSoundID]->mSound.play();
		mDraw = true;
	}
}

int VoiceDialog::getDialogID()
{
	if(playingSoundID >= mSounds.size()-1)
		if(mSounds[playingSoundID]->mSound.getStatus() == sf::Sound::Stopped)
			return playingSoundID;
		else
			return -1;
	else
		return -1;
}

void VoiceDialog::tick()
{
	if(mMapID == 7 && playingSoundID >= 5 && playingSoundID < 10)
	{
		if(playingSoundID == 9 && mSounds[playingSoundID]->mSound.getStatus() != sf::Sound::Stopped)
			pause = 20;
		if(playingSoundID < mSounds.size()-1)
			if(mSounds[playingSoundID]->mSound.getStatus() == sf::Sound::Stopped && pause <= 0)
				playNextDialog();
			else
				pause -= .5;
	}

	if(playingSoundID <= mSounds.size()-1 && pause <= 0 && mSounds.size() > 0)
		if(mSounds[playingSoundID]->mSound.getStatus() == sf::Sound::Stopped)
			mDraw = false;
}

void VoiceDialog::render(sf::RenderWindow *target)
{
	if(mDraw)
	{
		mRS.setPosition(target->getPosition().x+target->getSize().x/2-mRS.getSize().x/2,target->getSize().y-mRS.getSize().y);
		target->draw(mRS);
		mText.setString(mSounds[playingSoundID]->mText);
		mText.setPosition(mRS.getPosition().x+270,mRS.getPosition().y+50);
		target->draw(mText);
	}
}
