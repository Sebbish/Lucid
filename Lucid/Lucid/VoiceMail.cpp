#include "VoiceMail.h"


VoiceMail::VoiceMail(int mapID):
	mActiveSoundID(0)
{
	loadSounds(mapID);
}


VoiceMail::~VoiceMail()
{
}

void VoiceMail::newMap(int mapID)
{
	/*while(mActiveSounds.size() >= 1)
		mActiveSounds.pop_back();
	while(mSounds.size() >= 1)
	{
		delete mSounds[mSounds.size()-1];
		mSounds.pop_back();
	}*/
	loadSounds(mapID);
}

void VoiceMail::playNextSound()
{
	stop();
	mActiveSoundID++;
	mSounds[mActiveSoundID]->mSound.play();
}

void VoiceMail::activateNextSound()
{
	if(mActiveSounds.size() <= mActiveSounds.size()-1)
		mActiveSounds.push_back(mSounds[mActiveSounds.size()]);
}

void VoiceMail::playSound(int ID)
{
	stop();
	mSounds[ID]->mSound.play();
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


void VoiceMail::loadSounds(int mapID)
{

}