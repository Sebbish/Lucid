#include "VoiceMail.h"


VoiceMail::VoiceMail(int mapID):
	mActiveSoundID(0)
{
	loadSounds(mapID);
	mSounds.push_back(new mSoundSlot("1","P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/door 2 0,75sec.wav"));
	mSounds.push_back(new mSoundSlot("2","P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/door 2 0,75sec.wav"));
	mSounds.push_back(new mSoundSlot("3","P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/door 2 0,75sec.wav"));
	mSounds.push_back(new mSoundSlot("4","P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/door 2 0,75sec.wav"));
	mSounds.push_back(new mSoundSlot("5","P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/door 2 0,75sec.wav"));
	mSounds.push_back(new mSoundSlot("6","P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/door 2 0,75sec.wav"));
	mSounds.push_back(new mSoundSlot("7","P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/door 2 0,75sec.wav"));
	mSounds.push_back(new mSoundSlot("8","P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/door 2 0,75sec.wav"));
	mSounds.push_back(new mSoundSlot("9","P:/Downloads/LucidProject/Resources/Sound/SoundFX/MONO sound fx/door 2 0,75sec.wav"));
	mActiveSounds.push_back(mSounds[0]);
	mActiveSounds.push_back(mSounds[1]);
	mActiveSounds.push_back(mSounds[2]);
	mActiveSounds.push_back(mSounds[3]);
	mActiveSounds.push_back(mSounds[4]);
	mActiveSounds.push_back(mSounds[5]);
	mActiveSounds.push_back(mSounds[6]);
	mActiveSounds.push_back(mSounds[7]);
	mActiveSounds.push_back(mSounds[8]);
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