#include "VoiceDialog.h"


VoiceDialog::VoiceDialog(sf::Texture *t):
	playingSoundID(-1),mTexture(t)
{
	mFont.loadFromFile("LucidProject/Resources/Dialog/ariblk.ttf");
	mText.setFont(mFont);
	mDraw = false;
	mRS.setSize(sf::Vector2f(960,200));
	mRS.setFillColor(sf::Color::White);
	mRS.setTexture(mTexture);
	pause = 0.0;
	lvl8Thing = false;
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
	std::string newLine;
	newLine = '\n';
	while(mSounds.size() > 0)
	{
		delete mSounds[mSounds.size()-1];
		mSounds.pop_back();
	}
	switch (mapID)
	{
	case 14:
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Taunt_Businesswoman","Hey captain! Nice job breaking"+newLine+"everything"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Taunt_Moneyback","I demand my money back!"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Taunt_Oldlady","Well hurry up then, boat's not gonna"+newLine+"steer itself!"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Taunt_Oldman","Do something! You're the captain"+newLine+"right?!"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Taunt_MrGreen","Are….are we going to die?"));

		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Texasman_1","Look son, there goes the captain,"+newLine+"what a sorry sight to see right?"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Pojkvasker_1","But you said captains are super cool"+newLine+"guys who get to use that big steering"+newLine+"wheel. "));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Texasman_2","Well most of them are, this one is just"+newLine+"a big lazy bum though."));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Pojkvasker_2","Dad?"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Texasman_3","Yes?"));
		mSounds.push_back(new mSoundSlot("Boatscene_2/Boatscene_2_Pojkvasker_3","I don't want to be a captain when I"+newLine+"grow up, I think it looks hard and you"+newLine+"will just get sad like him"));
		break;
	case 13:
		mSounds.push_back(new mSoundSlot("Boatscene_1/Boatscene_1_Hippie_1","Can´t believe we never tried this cruise"+newLine+"thing before, the bars look really dope"+newLine+"man!"));
		mSounds.push_back(new mSoundSlot("Boatscene_1/Boatscene_1_MrGreen_1","Yeah, I can´t wait until people start drinking."+newLine+"Maybe we should ask those girls next doors"+newLine+"if they want to tag along?"));
		mSounds.push_back(new mSoundSlot("Boatscene_1/Boatscene_1_Hippie_2","Totally, they looked pretty good and seemed pretty cool"+newLine+"actually. I don´t know about you but I have a feeling that it"+newLine+"was a better choice to spend our money on this cruise"+newLine+"than following Dan and Doyle on their beer road trip."));
		mSounds.push_back(new mSoundSlot("Boatscene_1/Boatscene_1_MrGreen_2","Well that probably would have been"+newLine+"alot cheaper though. By the way, did"+newLine+"you see the captain before?"));
		mSounds.push_back(new mSoundSlot("Boatscene_1/Boatscene_1_Hippie_3","Yeah man, what´s up with that posture? He"+newLine+"totally ruined my picture of a captain.I"+newLine+"thought they were supposed to be totally"+newLine+"alpha"));
		mSounds.push_back(new mSoundSlot("Boatscene_1/Boatscene_1_MrGreen_3","Doesn´t matter, as soon as he enters the bar"+newLine+"wearing his uniform, then all the girls will look"+newLine+"at him anyway"));
		mSounds.push_back(new mSoundSlot("Boatscene_1/Boatscene_1_Hippie_4","Ooh yeah, I bet a guy like him exploits that as"+newLine+"much as he can. I would be so surprised if I"+newLine+"did not see him there tonight"));
		mSounds.push_back(new mSoundSlot("Boatscene_1/Boatscene_1_Helmsman","Oh Lewis, are you slacking off again?"+newLine+"Hurry up, people are looking for you"));
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
		if(mMapID == 8 && (playingSoundID == 1 ||playingSoundID == 4 || playingSoundID == 5 || playingSoundID == 6))
			mText.setCharacterSize(25);
		else if(mMapID == 8 && playingSoundID == 2)
			mText.setCharacterSize(20);
		else
			mText.setCharacterSize(30);
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

void VoiceDialog::boatLvl8Thing()
{
	if(mMapID == 13)
	{
		for(int i = 0; i < mSounds.size()-2;i++)
		{
			mSounds[i]->mSound.setVolume(50);
		}
		mSounds[mSounds.size()-1]->mSound.play();
		lvl8Thing = true;
	}
}

bool VoiceDialog::playingLvl8Thing()
{
	if(mMapID ==  13 && lvl8Thing)
	{
		if(mSounds[mSounds.size()-1]->mSound.getStatus() == sf::Sound::Stopped)
			return true;
	}
	return false;
}

void VoiceDialog::tick()
{
	if(mMapID == 14 && playingSoundID >= 5 && playingSoundID < 10)
	{
		if(playingSoundID == 9 && mSounds[playingSoundID]->mSound.getStatus() != sf::Sound::Stopped)
			pause = 20;
		if(playingSoundID < mSounds.size()-1)
			if(mSounds[playingSoundID]->mSound.getStatus() == sf::Sound::Stopped && pause <= 0)
				playNextDialog();
			else
				pause -= .5;
	}
	if(mMapID == 13)
	{
		if(playingSoundID == -1)
		{
			playNextDialog();
		}else if(playingSoundID < mSounds.size()-2)
		{
			if(mSounds[playingSoundID]->mSound.getStatus() == sf::Sound::Stopped)
				playNextDialog();
		}
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
		if(mMapID == 8 && mSounds[mSounds.size()-1]->mSound.getStatus() == sf::Sound::Playing)
		{
			mText.setString(mSounds[mSounds.size()-1]->mText);
			mText.setPosition(mRS.getPosition().x+270,mRS.getPosition().y+50);
		}else
		{
			mText.setString(mSounds[playingSoundID]->mText);
			mText.setPosition(mRS.getPosition().x+270,mRS.getPosition().y+50);
		}
		target->draw(mText);
	}
}
