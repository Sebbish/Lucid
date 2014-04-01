#include "VoiceMail.h"


VoiceMail::VoiceMail(int mapID,sf::Texture* Voicemail):
	mActiveSoundID(-1),mSoundPlayingID(-1),mTexture(Voicemail)
{
	loadSounds(mapID);
	mFont.loadFromFile("../../../LucidProject/Resources/Dialog/ariblk.ttf");
	//mFont.loadFromFile("P:/Downloads/LucidProject/Resources/Dialog/ariblk.ttf");
	mText.setFont(mFont);
	mDraw = false;
	mRS.setSize(sf::Vector2f(960,200));
	mRS.setFillColor(sf::Color::White);
	mRS.setTexture(mTexture);
}


VoiceMail::~VoiceMail()
{
}

void VoiceMail::newMap(int mapID)
{
	mDraw = false;
	loadSounds(mapID);
	mActiveSoundID = -1;
}

void VoiceMail::playNextSound()
{
	stop();
	if(mActiveSoundID <= mActiveSounds.size()-1)
	{
		mActiveSoundID++;
		mActiveSounds[mActiveSoundID]->mSound.play();
	}
}

void VoiceMail::activateNextSound(bool play)
{
	if(mActiveSounds.size() <= mSounds.size())
		mActiveSounds.push_back(mSounds[mActiveSounds.size()]);
	if(play)
		playSound(mActiveSounds.size()-1);
}

void VoiceMail::playSound(int ID)
{
	stop();
	mSoundPlayingID = ID;
	if(ID >= 0 && ID <= mActiveSounds.size()-1)
	{
		mActiveSounds[ID]->mSound.play();
		mDraw = true;
	}
}

void VoiceMail::stop()
{
	for(auto i:mSounds)
		i->mSound.stop();
}

int VoiceMail::getActiveSoundID()
{
	return mActiveSoundID;
}

void VoiceMail::nextPrevSoundSlot(bool next)
{
	if(next)
	{
		if(mActiveSoundID >= mActiveSounds.size()-1)
			mActiveSoundID = 0;
		else
			mActiveSoundID++;
	}else
	{
		if(mActiveSoundID <= 0)
			mActiveSoundID = mActiveSounds.size()-1;
		else
			mActiveSoundID--;
	}
}

std::vector<VoiceMail::mSoundSlot*> VoiceMail::getSounds()
{
	return mActiveSounds;
}

void VoiceMail::tick()
{
	if(mDraw)
		if(mActiveSounds[mSoundPlayingID]->mSound.getStatus() == sf::Music::Stopped)
			mDraw = false;

}

void VoiceMail::render(sf::RenderWindow *target)
{
	if(mDraw)
	{
		mRS.setPosition(target->getPosition().x+target->getSize().x/2-mRS.getSize().x/2,target->getSize().y-mRS.getSize().y);
		target->draw(mRS);
		mText.setString(mActiveSounds[mSoundPlayingID]->mText);
		mText.setPosition(mRS.getPosition().x+270,mRS.getPosition().y+50);
		target->draw(mText);
	}
}


void VoiceMail::loadSounds(int mapID)
{
	while(mActiveSounds.size() >= 1)
		mActiveSounds.pop_back();
	while (mSounds.size() >= 1)
	{
		delete mSounds[mSounds.size()-1];
		mSounds.pop_back();
	}
	std::string a;
	a = '\n';
	for(int i = 1; i <= mapID; i++)
		switch(i)
		{
		case 2:
			mSounds.push_back(new mSoundSlot("Welcome","welcome to saint hermelin new 01 ( high sanity)","Welcome to St.Hermelin Hospital,"+a+"enjoy your stay... and don't touch"+a+"anything"));
			/*mSounds.push_back(new mSoundSlot("Who’s cleaning around here?","how sloppy whos cleaning around here new 01 ( high sanity)"));
			mSounds.push_back(new mSoundSlot("We couldn’t afford a plumber","i wonder what happened to the plummer 01 ( high sanity)"));
			mSounds.push_back(new mSoundSlot("Now what could that have been?","now what could that have been ( high sanity)"));*/
			mSounds.push_back(new mSoundSlot("A key","a key, it usually unlocks doors 03 ( high sanity)","a key, it usually unlocks doors"));
			//mSounds.push_back(new mSoundSlot("Someone must have left the tap on","someone has left the tap on 01 ( high sanity)"));
			if(mapID == 2)
				activateNextSound(true);
			else if(mapID > 2)
			{
				activateNextSound(false);
				activateNextSound(false);
			}
			break;
		case 3:
			mSounds.push_back(new mSoundSlot("Hide","seems like a bad idea to stand there in the open 01 ( high sanity)","seems like a bad idea to stand there"+a+"in the open"));
			mSounds.push_back(new mSoundSlot("boo","boo 09 ( high sanity)","..."));
			mSounds.push_back(new mSoundSlot("sorry","sorry about that  ( high sanity)","sorry about that"));
			if(mapID > 3)
			{
				activateNextSound(false);
				activateNextSound(false);
				activateNextSound(false);
			}
			break;
		case 4:
			mSounds.push_back(new mSoundSlot("MindControl","what if you could control that thing  ( high sanity)","What if you could control that thing?"+ a +"It's faster than you, lighter than you"+a+"and more importantly, better looking"));
			mSounds.push_back(new mSoundSlot("See what I mean","It can even open doors  ( high sanity)","See what I mean, it can even open "+a+"doors, something you've been"+a+"struggling with for a while now"));
			if(mapID > 4)
			{
				activateNextSound(false);
				activateNextSound(false);
			}
			break;
		}
}